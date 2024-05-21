import QtQuick 2.15
import QtQuick.Controls 2.15

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
        Label {
            id: labeldialog
            text: "Change port successfully!"
        }
    }
}
