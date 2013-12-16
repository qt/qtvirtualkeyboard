import QtQuick 2.0

/*!
    \qmltype SelectionListItem
    \inqmlmodule QtVkb.Styles
    \brief A base type for selection list item delegates.

    The SelectionListItem enables mouse handling for the selection list item
    delegates.
*/

Item {
    id: selectionListItem
    height: parent.height
    MouseArea {
        id: mouseArea
        anchors.fill: parent
        hoverEnabled: true
        onClicked: selectionListItem.ListView.view.model.itemSelected(index)
    }
}
