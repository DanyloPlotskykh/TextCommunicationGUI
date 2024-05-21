import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Layouts 1.15

ApplicationWindow {
    id: chatWindow
    visible: true
    width: 400
    height: 600
    title: qsTr("Chat Application")

    Connections {
        target: backend
        function onNewMessage(message) {
            messageModel.append({"message": message});
        }
        function onConnectionStatusChanged() {
            correctDialog.open()
        }
        function onIncorrectPort() {
            inCorrectDialog.open()
        }
        function onConncetToServerFailed() {
            failedConnectToServerDialog.open()
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
                text: qsTr("Connect")
                Layout.fillWidth: true
                onClicked: {
                    backend.onButtonClick()
                }
            }
            Button {
                text: qsTr("Change Port")
                Layout.fillWidth: true
                onClicked: {
                    changePortDialog.open()
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
                        onEditingFinished: 
                        {
                            if (messageInput.text !== "") {
                                server.onSubmitClk(messageInput.text)
                                messageInput.text = ""
                            }
                        }
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

    ListModel {
        id: messageModel
    }

    ChangePortDialog {
        id: changePortDialog
    }

    CorrectDialog {
        id: correctDialog
    }

    IncorrectDialog {
        id: inCorrectDialog
    }

    FailedConnectToServerDialog {
        id: failedConnectToServerDialog
    }
}
