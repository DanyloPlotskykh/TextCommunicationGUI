import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Layouts 1.15

Rectangle {
    width: Math.min(contentItem.implicitWidth + 20, 400) // Устанавливаем ширину виджета в зависимости от ширины содержимого
    height: Math.min(contentItem.implicitHeight + 20, 400) // Устанавливаем высоту виджета в зависимости от высоты содержимого
    color: "orange"
    border.color: "blue"
    radius: 10
    clip: true // Ограничиваем содержимое виджета его границами

    Text {
        id: contentItem
        text: "Длинный текст, который может быть переменной длины. Этот текст будет автоматически переноситься на новую строку, если он не помещается в одну строку. Исходя из длины текста, размеры виджета будут подстраиваться для отображения всего содержимого."
        wrapMode: Text.Wrap // Устанавливаем режим переноса текста
        color: "black"
    }
}
