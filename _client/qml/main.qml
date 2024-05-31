import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Layouts 1.15

ApplicationWindow {
    id: chatWindow
    visible: true
    width: 400
    height: 600
    title: qsTr("Chat Application")
    color: "#151324"

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
        function onDeleteQmlMessage(id) {
            messageModel.remove(id)
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
                background: Rectangle {
                    Layout.fillWidth: true
                    Layout.fillHeight: true
                    color: "#554991"
                    radius: 5
                    border.color: "#000000"
                }
                onClicked: {
                    backend.onButtonClick()
                }
            }
            Button {
                text: qsTr("Change Port")
                Layout.fillWidth: true
                background: Rectangle {
                    Layout.fillWidth: true
                    Layout.fillHeight: true
                    color: "#554991"
                    radius: 5
                    border.color: "#000000"
                }
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
                        color: "#ffffff"
                    }
                    Button {
                        text: qsTr("Delete")
                        background: Rectangle {
                            color: "#554991"
                            radius: 5
                            border.color: "#000000"
                        }
                        onClicked: {
                            backend.onDeleteBtnClick(index)
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
                 color: "#ffffff"
                placeholderText: qsTr("Enter message here...")
                background: Rectangle {
                    color: "#3c384f" // Цвет фона
                    radius: 4
                }
                onEditingFinished: 
                {
                    if (messageInput.text !== "") {
                        backend.onSubmitBtnClick(messageInput.text)
                        messageInput.text = ""
                    }
                }
            }

            Button {
                text: qsTr("Send")
                background: Rectangle {
                    height: 100
                    color: "#554991"
                    radius: 5
                    border.color: "#000000"
                }
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
