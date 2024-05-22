import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Layouts 1.15

Dialog {
    id: dialog
    title: "Change Port"
    visible: false
    modal: true

    Component.onCompleted: {
        dialog.x = (parent.width - dialog.width) / 2;
        dialog.y = (parent.height - dialog.height) / 2;
    }

    contentItem: Column {
        spacing: 10
        width: parent.width
        padding: 20

        Text {
            text: "Enter the port number"
            wrapMode: Text.WordWrap
        }

        TextField {
            id: portfield
            Layout.fillWidth: true
            color: "#ffffff"
            background: Rectangle {
                    color: "#3c384f" // Цвет фона
                    radius: 4
            }
            placeholderText: qsTr("Enter port here...")
        }
        RowLayout {
            id: dialogRow
            Layout.fillWidth: true
            spacing: 10

            Button {
                text: qsTr("Change")
                Layout.fillWidth: true
                background: Rectangle {
                        color: "#554991"
                        radius: 5
                        border.color: "#000000"
                    }
                onClicked: {
                    var message = portfield.text;
                    backend.onChangePortClick(message)
                    portfield.text = ""
                    dialog.close()
                }
            }
            Button {
                text: qsTr("Cancel")
                Layout.fillWidth: true
                background: Rectangle {
                        color: "#554991"
                        radius: 5
                        border.color: "#000000"
                    }
                onClicked: {
                    dialog.close()
                }
            }
        }
    }
}
