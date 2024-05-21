import QtQuick 2.15
import QtQuick.Controls 2.15

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
        Label {
            id: inclabeldialog
            text: "Change port failed!"
        }
    }
}
