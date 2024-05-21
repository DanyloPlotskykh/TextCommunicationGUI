import QtQuick 2.15
import QtQuick.Controls 2.15

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
        Label {
            id: failedServerlabeldialog
            text: "Connect to server failed!"
        }
    }
}
