import QtQuick 2.15
import QtQuick.Controls 2.15

ApplicationWindow {
    visible: true
    width: 400
    height: 600
    title: "Server"

    // Button
    // {
    //     id: connectbtn
    // }
    ListModel {
        id: chatModel
    }

    Column {
        anchors.fill: parent
        spacing: 10

        ListView {
            id: chatListView
            width: parent.width
            height: parent.height - sendRow.height - 20 

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
                    backend.onSubmitClk(message)
                    if (message !== "") {
                        chatModel.append({ "message": message })
                        messageInput.text = ""
                    }
                }
            }
        }
    }
}
