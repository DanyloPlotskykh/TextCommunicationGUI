import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Layouts 1.15
import com.example.server 1.0

ApplicationWindow {
    visible: true
    width: 400
    height: 600
    title: "Server"

    Server {
        id: server
    }

    Connections {
        target: server
        function onNewMessage(message) {
            chatModel.append({"message": message})
        }
        function onConnectionStatusChanged() {
            correctDialog.open()
        }
        function onIncorrectPort() {
            inCorrectDialog.open()
        }
    }

    ListModel {
        id: chatModel
    }

    ColumnLayout {
        anchors.fill: parent

        RowLayout {
            width: parent.width
            height: startButton.height
            spacing: 10

            Button {
                id: startButton
                text: "Start Server"
                onClicked: server.startServer()
                Layout.fillWidth: true
            }

            // CustomButton {
            //     id: startButton
            //     Layout.fillWidth: true
            // }

            Button {
                id: changePortButton
                text: "Change Port"
                onClicked: {
                    changePortDialog.open();
                }
                Layout.fillWidth: true
            }
        }

        ListView {
            id: chatListView
            Layout.fillWidth: true
            Layout.fillHeight: true

            model: chatModel
            delegate: RowLayout {
                width: parent.width
                spacing: 10

                Text {
                    text: model.message
                    wrapMode: Text.Wrap
                    font.pixelSize: 14
                    color: "black"
                    padding: 10
                }

                Button {
                    text: "Delete"
                    onClicked: {
                        chatModel.remove(index)
                    }
                }
            }
        }

        RowLayout {
            id: buttonsRow
            Layout.fillWidth: true
            Layout.alignment: Qt.AlignBottom
            spacing: 10

            TextField {
                id: messageInput
                Layout.fillWidth: true
                placeholderText: qsTr("Enter message here...")
                onEditingFinished: 
                {
                    if (messageInput.text !== "") {
                        server.onSubmitClk(messageInput.text)
                        messageInput.text = ""
                    }
                }
            }

            Button {
                text: qsTr("Send")
                onClicked: {
                    if (messageInput.text !== "") {
                        server.onSubmitClk(messageInput.text)
                        messageInput.text = ""
                    }
                }
            }
        }
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
}
