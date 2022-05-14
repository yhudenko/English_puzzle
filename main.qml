﻿import QtQuick 2.15
import QtQuick.Window 2.15

Window {
    id: root
    width: 640
    height: 480
    visible: true
    title: qsTr("English_puzzle")

    GameBoard{
        id: _gameBoard
        anchors.fill: parent
        anchors.margins: 5
    }

}
