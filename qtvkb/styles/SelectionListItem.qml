import QtQuick 2.0

Item {
    id: selectionListItem
    MouseArea {
        id: mouseArea
        anchors.fill: parent
        hoverEnabled: true
        onClicked: selectionListItem.ListView.view.model.itemSelected(index)
    }
}
