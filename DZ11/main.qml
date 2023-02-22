import QtQuick 2.12
import QtQuick.Window 2.15
import QtQuick.Controls 2.15
import SaveUser 1.0
import QtQuick.Layouts 1.3

Window {
    id: root
    width: 700
    height: 200
    visible: true
    title: qsTr("Organaizer")

    SaveUser {
        id: taskList
    }
    MyButton {
        id: myButton
        anchors.bottom: parent.bottom
        anchors.right: parent.right
        anchors.bottomMargin: 20
        anchors.rightMargin: 32
        enabled: (taskEdit.text !== "" && date.acceptableInput && progress.acceptableInput) ? true : false
        onClicked: {
            taskList.addTasc(taskEdit.text, date.text, progress.text)
            newT.text = " New task: " + taskList.getNewTascs()
            oldT.text = " All: " + taskList.getTascsCount()
        }
    }

    Button {
        id: butdb
        text: qsTr("Tasks database")
        anchors.bottom: myButton.top
        anchors.right: parent.right
        anchors.bottomMargin:0
        anchors.rightMargin: 32
        width: 100
        height: 25
        background: Rectangle {
            color: butdb.pressed ? "lawngreen" : "beige"
            border.color: butdb.pressed ? "lightgreen" : "black"
            border.width: 2
            radius: 5
        }
        onClicked: {
            taskList.viewTascs()
        }
    }

    Rectangle {
        anchors.fill: parent
        z: -2
        border.width: 2
        radius: 5
        color: "bisque"

    }
    Rectangle {
        id: mainrec
        anchors.top: parent.top
        anchors.right: parent.right
        anchors.left: parent.left
        anchors.bottom: parent.bottom
        anchors.margins: 20
        color: "bisque"
        border.color: "black"
        border.width: 2
        radius: 5
        z: -1
        Row {
            id: row
            spacing: 5
            anchors.right: parent.right
            anchors.left: parent.left
            anchors.bottom: parent.bottom
            height: 50
            Rectangle {
                height: parent.height
                width: parent.width/5
                clip: true
                color: "beige"
                border.color: "black"
                border.width: 2
                radius: 5
                TextField {
                    id:taskEdit
                    placeholderText: "Enter task:"
                    background: Rectangle {
                    color: "transparent"
                    }
                }
            }
            Rectangle {
                height: parent.height
                width: parent.width/5
                clip: true
                color: "beige"
                border.color: "black"
                border.width: 2
                radius: 5
                TextField {
                    id:date
                    placeholderText: "Enter date: dd.mm.yyyy "
                    validator: RegularExpressionValidator { regularExpression: /[0-9]{2}\.[0-9]{2}\.[0-9]{4}/ }
                    background: Rectangle {
                    color: "transparent"
                    }
                }
            }
            Rectangle {
                height: parent.height
                width: parent.width/5
                clip: true
                color: "beige"
                border.color: "black"
                border.width: 2
                radius: 5
                TextField {
                    id:progress
                    placeholderText: "Enter progress: 0-10 "
                    validator: RegularExpressionValidator { regularExpression: /[0-9]{1}|[1]{1}[0]{1}/ }
                    background: Rectangle {
                    color: "transparent"
                    }
                }
            }
            Rectangle {
                height: parent.height
                width: parent.width/5
                color: "beige"
                border.color: "black"
                border.width: 2
                radius: 5
            Column {
                Text {
                    id:newT
                    anchors.horizontalCenter: parent.horizontalLeft
                    text: " New tasks: " + taskList.getNewTascs()
                      }
                Text {
                     id:oldT
                     anchors.horizontalCenter: parent.horizontalLeft
                     text: " Old tasks: " + taskList.getTascsCount()
                       }
                    }
                }
            }
        }
    }
