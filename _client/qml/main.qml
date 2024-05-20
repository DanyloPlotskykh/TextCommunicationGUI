import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Layouts 1.15
import com.example.networki 1.0

ApplicationWindow {
    id: chatWindow
    visible: true
    width: 400
    height: 600
    title: qsTr("Chat Application")

    Network {
        id: network
    }

    Connections {
        target: backend
        function onNewMessage(message) {
            messageModel.append({"message": message});
        }
    }

    ColumnLayout {
        anchors.fill: parent
        spacing: 10

        RowLayout {
            id: buttonsRow
            Layout.fillWidth: true
            spacing: 10

            Button {
                text: qsTr("Подключиться")
                Layout.fillWidth: true
                onClicked: {
                    backend.onButtonClick()
                }
            }
            Button {
                text: qsTr("Change Port")
                Layout.fillWidth: true
                onClicked: {
                    dialog.open()
                }
            }
        }

        ListView {
            id: messageListView
            Layout.fillWidth: true
            Layout.fillHeight: true
            model: messageModel
            delegate: Item {
                width: parent.width
                height: messageText.paintedHeight + 20
                RowLayout {
                    anchors.fill: parent
                    spacing: 10
                    Text {
                        id: messageText
                        text: model.message
                        wrapMode: Text.Wrap
                        Layout.fillWidth: true
                    }
                    Button {
                        text: qsTr("Delete")
                        onClicked: {
                            messageModel.remove(index)
                        }
                    }
                }
            }
        }

        RowLayout {
            width: parent.width
            spacing: 10

            TextField {
                id: messageInput
                Layout.fillWidth: true
                placeholderText: qsTr("Enter message here...")
            }

            Button {
                text: qsTr("Send")
                onClicked: {
                    if (messageInput.text !== "") {
                        backend.onSubmitBtnClick(messageInput.text)
                        messageInput.text = ""
                    }
                }
            }
        }
    }

    Dialog {
        id: dialog
        title: "Change Port"
        visible: false

        contentItem: Column {
            spacing: 10
            width: parent.width
            padding: 20

            Text {
                text: "This is a dialog message."
                wrapMode: Text.WordWrap
            }

            TextField {
                id: portfield
                Layout.fillWidth: true
                placeholderText: qsTr("Enter port here...")
            }
            RowLayout
            {
                id: dialogRow
                Layout.fillWidth: true
                spacing: 10

                Button {
                    text: qsTr("Change")
                    Layout.fillWidth: true
                    onClicked: {
                        // backend.onButtonClick()
                        var message = portfield.text;
                        backend.onChangePortClick(message)
                        portfield.text = ""
                        dialog.close()
                    }
                }
                Button {
                    text: qsTr("Cancel")
                    Layout.fillWidth: true
                    onClicked: {
                        dialog.close()
                    }
                }
            }
        }
    }

    Dialog {
        id: correctDialog        
    }

    ListModel {
        id: messageModel
    }
}
