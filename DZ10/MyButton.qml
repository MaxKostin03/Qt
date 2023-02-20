import QtQuick 2.12
import QtQuick.Window 2.12
import QtQuick.Controls 2.15
import SaveUser 1.0


Button {
    id: myButton
    width: 100
    height: 50
    contentItem: Text {
        anchors.horizontalCenter: parent.horizontalCenter
        text: "WRITE"
        color: myButton.pressed ? "#lawngreen" : "black"
    }

    ToolTip.visible: myButton.enabled ? false : hovered
    ToolTip.text: qsTr("Please, enter correct data")

    background: Rectangle {
        color: myButton.pressed ? "lawngreen" : "beige"
        border.color: myButton.pressed ? "lightgreen" : "black"
        border.width: 2
        radius: 5
    }

}
