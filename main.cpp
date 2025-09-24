#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include <QProcess>
#include <QObject>
#include <QString>
#include <sailfishapp.h>

class ShellRunner : public QObject {
    Q_OBJECT
public:
    explicit ShellRunner(QObject *parent = nullptr) : QObject(parent) {}

    Q_INVOKABLE QString runWithDevelSu() {
        QProcess proc;

        // "-p" means prompt for password (GUI or terminal depending on environment)
        QStringList args = {"-p", "pkill", "msg-eng"};

        proc.start("devel-su", args);
        bool finished = proc.waitForFinished(5000);  // 5 seconds timeout

        QString stdOut = proc.readAllStandardOutput();
        QString stdErr = proc.readAllStandardError();

        if (!finished) {
            return "Error: Command timed out.";
        }

        if (!stdErr.isEmpty())
            return "Error: " + stdErr.trimmed();

        return "Success: " + stdOut.trimmed();
    }
};

int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);
    QQmlApplicationEngine engine;

    ShellRunner runner;
    engine.rootContext()->setContextProperty("ShellRunner", &runner);

    engine.load(SailfishApp::pathTo("qml/Main.qml"));
    return app.exec();
}

#include "main.moc"
