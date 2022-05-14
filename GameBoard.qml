import QtQuick 2.0
import Game 1.0

GridView {
    id: root

    model: GameBoardModel{

    }
    cellWidth: width / root.model.colums
    cellHeight: height / root.model.rows

    interactive: false

    delegate: Item{
        id: _backgroundDelegate
        width: cellWidth
        height: cellHeight

        visible: display != ""

        Tile{
            anchors.fill: _backgroundDelegate
            anchors.margins: 5
            internalText.text: display
            MouseArea{
                anchors.fill: parent
                onClicked: {
                    root.model.action(index);
                }
            }
        }
    }
}
