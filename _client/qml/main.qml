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
        function onConnectionStatusChanged() 
        {
            correctDialog.open()
        }
        function onIncorrectPort() 
        {
            inCorrectDialog.open()
        }
        function onConncetToServerFailed()
        {
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
                        // correctDialog.open()
                    }
                }
            }
        }
    }

    Dialog {
        id: correctDialog  
        title: ""
        visible: false
        modal: true

        standardButtons: Dialog.Ok

        Component.onCompleted: {
            correctDialog.x = (parent.width - correctDialog.width) / 2;
            correctDialog.y = (parent.height - correctDialog.height) / 2;
        }      

        contentItem: Column {
            Label
            {
                id: labeldialog
                text: "Change port successfully!"
            }
        }
    }

    Dialog {
        id: inCorrectDialog  
        title: ""
        visible: false
        modal: true

        standardButtons: Dialog.Ok

        Component.onCompleted: {
            inCorrectDialog.x = (parent.width - inCorrectDialog.width) / 2;
            inCorrectDialog.y = (parent.height - inCorrectDialog.height) / 2;
        }      

        contentItem: Column {
            Label
            {
                id: inclabeldialog
                text: "Change port failed!"
            }
        }
    }

    Dialog {
        id: failedConnectToServerDialog  
        title: ""
        visible: false
        modal: true

        standardButtons: Dialog.Ok

        Component.onCompleted: {
            failedConnectToServerDialog.x = (parent.width - failedConnectToServerDialog.width) / 2;
            failedConnectToServerDialog.y = (parent.height - failedConnectToServerDialog.height) / 2;
        }      

        contentItem: Column {
            Label
            {
                id: failedServerlabeldialog
                text: "Connect to server failed!"
            }
        }
    }

    ListModel {
        id: messageModel
    }
}
