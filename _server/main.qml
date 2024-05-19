import QtQuick 2.15
import QtQuick.Controls 2.15
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
    }

    ListModel {
        id: chatModel
    }

    Column {
        anchors.fill: parent
        spacing: 10

        Item {
            width: parent.width
            height: startButton.height

            Button {
                id: startButton
                text: "Start Server"
                onClicked: server.startServer()
            }
        }

        ListView {
            id: chatListView
            width: parent.width
            height: parent.height - sendRow.height - startButton.height - 30

            model: chatModel
            delegate: Row {
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

        Row {
            id: sendRow
            spacing: 10
            width: parent.width

            TextArea {
                id: messageInput
                width: parent.width - sendButton.width - 20
                height: 50
                placeholderText: "Enter the text..."
            }

            Button {
                id: sendButton
                text: "Send"
                onClicked: {
                    var message = messageInput.text.trim()
                    server.onSubmitClk(message)
                    if (message !== "") {
                        messageInput.text = ""
                    }
                }
            }
        }
    }
}
