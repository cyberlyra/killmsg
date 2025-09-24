import QtQuick 2.0
import Sailfish.Silica 1.0

Page {
    id: page
    allowedOrientations: Orientation.All

    SilicaFlickable {
        anchors.fill: parent
        contentHeight: column.height

        Column {
            id: column
            width: parent.width
            spacing: Theme.paddingLarge
            anchors.centerIn: parent

            Label {
                text: "Kill msg-eng (via devel-su)"
                font.pixelSize: Theme.fontSizeLarge
                horizontalAlignment: Text.AlignHCenter
                width: parent.width
            }

            Button {
                text: "Execute"
                onClicked: {
                    resultText = ShellRunner.runWithDevelSu()
                }
            }

            Label {
                text: resultText
                wrapMode: Text.Wrap
                width: parent.width * 0.9
            }
        }
    }

    property string resultText: ""
}
