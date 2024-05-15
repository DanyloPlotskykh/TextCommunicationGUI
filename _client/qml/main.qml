import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Layouts 1.15

ApplicationWindow {
    visible: true
    width: 800
    height: 400
    title: "Пример приложения"

    Rectangle {
        width: parent.width 
        height: parent.height 
        color: "lightblue"
        TextArea {
            id: texta
            implicitWidth: 500  // Фиксированная ширина
            implicitHeight: 300
            placeholderText: "Введите текст"
            font.pixelSize: 16        
        }
        Rectangle
        {
            width: texta.width
            anchors.top: texta.bottom
            TextField
            {
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
            anchors.left: texta.right 
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
                    onClicked: backend.onSubmitBtnClick()
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



// TextArea {
//     id: inputOutputArea
//     width: 200
//     height: 100
//     placeholderText: "Введите текст"
//     font.pixelSize: 16
//     wrapMode: Text.Wrap
//     anchors.horizontalCenter: parent.horizontalCenter
// }

// ColumnLayout {
//     spacing: 10 // Пространство между элементами
//     width: 200 // Ширина макета (может быть настроена в соответствии с вашими требованиями)

//     Text { text: "Элемент 1" }
//     Rectangle { width: 100; height: 50; color: "red" } // Пример элемента
//     Text { text: "Элемент 2" }
//     Rectangle { width: 100; height: 50; color: "blue" } // Пример элемента
// }