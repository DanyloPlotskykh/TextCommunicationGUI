import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Layouts 1.15
import com.example.server 1.0

ApplicationWindow {
    visible: true
    width: 400
    height: 600
    title: "Server"
    color: "#151324"
    Server {
        id: server
    }

    Connections {
        target: server
        function onNewMessage(message) {
            chatModel.append({"message": message}) // model should be implemented in C++
        }
        function onConnectionStatusChanged() {
            correctDialog.open()
        }
        function onIncorrectPort() {
            inCorrectDialog.open()
        }
        function onDeleteQmlMessage(id) {
            chatModel.remove(id)
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
                background: Rectangle {
                    Layout.fillWidth: true
                    Layout.fillHeight: true
                    color: "#554991"
                    radius: 5
                    border.color: "#000000"
                }
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
                background: Rectangle {
                    Layout.fillWidth: true
                    Layout.fillHeight: true
                    color: "#554991"
                    radius: 5
                    border.color: "#000000"
                }
                onClicked: {
                    changePortDialog.open();
                }
                Layout.fillWidth: true
            }
        }// Задание цвета фона

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
                    color: "#ffffff"
                    padding: 10
                }

                Button {
                    text: "Delete"
                    background: Rectangle {
                        color: "#554991"
                        radius: 5
                        border.color: "#000000"
                    }
                    onClicked: {
                        server.onDeleteBtnClick(index)
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
                color: "#ffffff"
                placeholderText: qsTr("Enter message here...")
                background: Rectangle {
                    color: "#3c384f" // Цвет фона
                    radius: 4
                }
                onEditingFinished: 
                {
                    if (messageInput.text !== "") { // !empty()
                        server.onSubmitClk(messageInput.text)
                        messageInput.text = ""
                    }
                }
            }

            Button {
                text: qsTr("Send Message")
                background: Rectangle {
                    height: 100
                    color: "#554991"
                    radius: 5
                    border.color: "#000000"
                }
                onClicked: {
                    if (messageInput.text !== "") { // copy paste
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
