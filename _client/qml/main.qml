import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Layouts 1.15

ApplicationWindow {
    visible: true
    width: 800
    height: 400
    title: "Пример приложения"

    // Компонент для создания кастомного элемента динамически
    Component {
        id: customItemComponent
        CustomItem {}
    }
    function createCustomItem(parent) {
        var customItem = customItemComponent.createObject(parent);
        customItem.x = Math.random() * (parent.width - customItem.width); // Устанавливаем случайное положение по X
        customItem.y = Math.random() * (parent.height - customItem.height); // Устанавливаем случайное положение по Y
        customItem.parent = textHistory
    }
    Rectangle {
        width: parent.width 
        height: parent.height 
        color: "lightblue"
        Rectangle
        {
            id: textHistory
            implicitWidth: 500  // Фиксированная ширина
            implicitHeight: 300
        }
        // TextArea {
        //     id: texta
        //     implicitWidth: 500  // Фиксированная ширина
        //     implicitHeight: 300
        //     placeholderText: "Введите текст"
        //     font.pixelSize: 16        
        // }
        Rectangle
        {
            width: textHistory.width
            anchors.top: textHistory.bottom
            TextField
            {
                id: lineEdit
                objectName: "lineEdit"
                width: parent.width
                height: parent.height
                placeholderText: "Enter the text..."
            }
        }
        Rectangle
        {
            color: "green"
            implicitWidth: 300 
            implicitHeight: 400
            anchors.left: textHistory.right 
            ColumnLayout {
                spacing: 10
                anchors.centerIn: parent
                Button {
                    id: connectbtn
                    text: "Connect"
                    // anchors.centerIn: parent
                    onClicked: backend.onButtonClick()             
                }

                Button {
                    text: "Send Message"
                    // anchors.top: connectbtn.bottom
                    onClicked: { 
                        console.log("submitBtn")
                        createCustomItem(parent);
                        backend.onSubmitBtnClick()
                    }
                    //add an implementation for create new textIsland in smth 
                    //and get from textfield text
                }
                Button {
                    text: "Change port"
                    // anchors.top: connectbtn.bottom
                    // onClicked: backend.onSubmitBtnClick()
                }
            }
        } 
    }
}
