import QtQuick 2.15
import QtQuick.Controls 2.15


// Fix allignment
Rectangle {
            id: startButton
            width: parent.width / 2
            height: 50
            radius: 25
            color: "lightblue"
            border.color: "blue"
            border.width: 2

            property bool pressed: false

            Rectangle {
                width: startButton.width
                height: startButton.height
                radius: startButton.radius
                color: startButton.pressed ? "blue" : "lightgrey"
                opacity: 0.5
                anchors.centerIn: startButton
                z: -1
            }

            Text {
                text: "Нажми меня" // What is that?
                anchors.centerIn: parent
                font.pixelSize: 20
                color: "white"
            }

            MouseArea {
                id: mouseArea
                anchors.fill: parent
                onPressed: {
                    startButton.pressed = true;
                }
                onReleased: {
                    startButton.pressed = false;
                    console.log("Button clicked!");
                }
            }

            ColorAnimation on color {
                targets: [startButton, startButton.children[0]]
                to: startButton.pressed ? "darkblue" : "lightblue"
                duration: 100
            }
        }