import QtQuick 2.12
import QtQuick.Window 2.15
import QtQuick.Controls 2.15
import SaveUser 1.0
import QtQuick.Layouts 1.3

Window {
    id: root
    width: 700
    height: 600
    visible: true
    title: qsTr("Organaizer")


    function addNetTask(task) {
        taskList.setTask(task)
    }

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
            addNetTask(taskEdit.text + " " + date.text + " " + progress.text)
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
                    id:numberNew
                    anchors.horizontalCenter: parent.horizontalLeft
                    text: " New tasks: " + taskList.newT
                        }
                 Text {
                        id:numberOld
                        anchors.horizontalCenter: parent.horizontalLeft
                        text: " Old tasks: " + taskList.oldT
                        }
                    }
                }
            }

        ListView {
            id: lv
                ScrollBar.vertical: ScrollBar {
                    active: hovered || pressed
                    hoverEnabled: true
                }
            anchors.top: parent.top
            anchors.right: parent.right
            anchors.left: parent.left
            anchors.bottom: row.top
            spacing: 10
            model: taskList.model
            delegate: Rectangle {
                anchors.right: parent.right
                anchors.left: parent.left
                height: 30
                radius: 5
                color: "beige"
                border.color: "black"
                border.width: 2
                Text { text: modelData; anchors.centerIn: parent }
                }
        }
    }
}
