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

        RowLayout {
            anchors.fill: parent 
            TextArea {
                width: 500
                placeholderText: "Введите текст"
                font.pixelSize: 16
                
            }
        
            ColumnLayout {
                spacing: 10

                Button {
                    text: "Кнопка 1"
                    onClicked: {
                        
                    }
                }

                Button {
                    text: "Кнопка 2"
                    onClicked: {
                        
                    }
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