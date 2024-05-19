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
            console.log("Received new message in QML: " + message); 
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
                    console.log("Button Clicked"); // Отладка
                    backend.onButtonClick()
                }
            }
            Button {
                text: qsTr("Change Port")
                Layout.fillWidth: true
                onClicked: {
                    // Your implementation here
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
                        text: qsTr("Удалить")
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
                placeholderText: qsTr("Введите сообщение")
            }

            Button {
                text: qsTr("Отправить")
                onClicked: {
                    if (messageInput.text !== "") {
                        backend.onSubmitBtnClick(messageInput.text)
                        messageModel.append({"message": messageInput.text})
                        messageInput.text = ""
                    }
                }
            }
        }
    }

    ListModel {
        id: messageModel
    }

    Component.onCompleted: {
        messageModel.append({"message": "Test message"});
    }
}
