import QtQuick 2.0

Rectangle {
    id: root
    property alias internalText: valueText
    color: "lightgreen"
    border{
        color: "black"
        width: 2
    }
    radius: 10

    Text{
        id: valueText
        text: " "

        font{
            pointSize: Math.min(root.width / 8, root.height / 2.5)
        }
        anchors.centerIn: root
    }
}
