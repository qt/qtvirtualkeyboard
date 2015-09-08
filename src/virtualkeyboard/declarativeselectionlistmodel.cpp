/******************************************************************************
**
** Copyright (C) 2015 The Qt Company Ltd
** All rights reserved.
** For any questions to The Qt Company, please use contact form at http://qt.io
**
** This file is part of the Qt Virtual Keyboard module.
**
** Licensees holding valid commercial license for Qt may use this file in
** accordance with the Qt License Agreement provided with the Software
** or, alternatively, in accordance with the terms contained in a written
** agreement between you and The Qt Company.
**
** If you have questions regarding the use of this file, please use
** contact form at http://qt.io
**
******************************************************************************/

#include "declarativeselectionlistmodel.h"
#include "abstractinputmethod.h"
#include <QtCore/private/qabstractitemmodel_p.h>

class DeclarativeSelectionListModelPrivate : public QAbstractItemModelPrivate
{
public:
    DeclarativeSelectionListModelPrivate() :
        QAbstractItemModelPrivate(),
        dataSource(0),
        type(DeclarativeSelectionListModel::WordCandidateList),
        rowCount(0)
    {
    }

    QHash<int, QByteArray> roles;
    AbstractInputMethod *dataSource;
    DeclarativeSelectionListModel::Type type;
    int rowCount;
};

/*!
    \qmltype SelectionListModel
    \instantiates DeclarativeSelectionListModel
    \inqmlmodule QtQuick.Enterprise.VirtualKeyboard
    \ingroup qtvirtualkeyboard-qml
    \brief Provides a data model for the selection lists.

    The SelectionListModel is a data model for word candidates
    provided by the input method.

    An instance of SelectionListModel cannot be created directly.
    Instead, the InputEngine manages the instances and provides
    access to the model by InputEngine::wordCandidateListModel
    property.

    The model exposes the following data roles for the list delegate:
    \list
        \li \c display Display text for item
        \li \c wordCompletionLength Word completion length for item
    \endlist

    The activeItemChanged signal indicates which item is currently
    highlighted by the input method. The view should respond to this
    signal by highlighting the corresponding item in the list.

    The user selection is handled by the selectItem() method. The view
    should be invoke this method when the user selects an item from the
    list.
*/

/*!
    \class DeclarativeSelectionListModel

    \inmodule InputFramework

    \brief List model for selection lists.

    This class acts as a bridge between the UI and the
    input method that provides the data for selection
    lists.
*/

/*!
    \enum DeclarativeSelectionListModel::Type

    This enum specifies the type of selection list.

    \value WordCandidateList
           Shows list of word candidates
*/

/*!
    \enum DeclarativeSelectionListModel::Role

    This enum specifies a role of the data requested.

    \value DisplayRole
           The data to be rendered in form of text.
    \value WordCompletionLengthRole
           An integer specifying the length of the word
           the completion part expressed as the
           number of characters counted from the
           end of the string.
*/

DeclarativeSelectionListModel::DeclarativeSelectionListModel(QObject *parent) :
    QAbstractListModel(*new DeclarativeSelectionListModelPrivate(), parent)
{
    Q_D(DeclarativeSelectionListModel);
    d->roles[DisplayRole] = "display";
    d->roles[WordCompletionLengthRole] = "wordCompletionLength";
}

/*!
    \internal
*/
DeclarativeSelectionListModel::~DeclarativeSelectionListModel()
{
}

/*!
    \internal
*/
void DeclarativeSelectionListModel::setDataSource(AbstractInputMethod *dataSource, Type type)
{
    Q_D(DeclarativeSelectionListModel);
    if (d->dataSource) {
        disconnect(this, SLOT(selectionListChanged(int)));
        disconnect(this, SLOT(selectionListActiveItemChanged(int, int)));
    }
    d->type = type;
    if (d->dataSource) {
        d->dataSource = 0;
        selectionListChanged(type);
        selectionListActiveItemChanged(type, -1);
    }
    d->dataSource = dataSource;
    if (d->dataSource) {
        connect(d->dataSource, SIGNAL(selectionListChanged(int)), SLOT(selectionListChanged(int)));
        connect(d->dataSource, SIGNAL(selectionListActiveItemChanged(int, int)), SLOT(selectionListActiveItemChanged(int, int)));
    }
}

/*!
    \internal
*/
AbstractInputMethod *DeclarativeSelectionListModel::dataSource() const
{
    Q_D(const DeclarativeSelectionListModel);
    return d->dataSource;
}

/*!
    \internal
*/
int DeclarativeSelectionListModel::rowCount(const QModelIndex &parent) const
{
    Q_D(const DeclarativeSelectionListModel);
    Q_UNUSED(parent)
    return d->rowCount;
}

/*!
    \internal
*/
QVariant DeclarativeSelectionListModel::data(const QModelIndex &index, int role) const
{
    Q_D(const DeclarativeSelectionListModel);
    return d->dataSource ? d->dataSource->selectionListData(d->type, index.row(), role) : QVariant();
}

/*!
    \internal
*/
QHash<int,QByteArray> DeclarativeSelectionListModel::roleNames() const
{
    Q_D(const DeclarativeSelectionListModel);
    return d->roles;
}

/*! \qmlmethod void SelectionListModel::selectItem(int index)

    This method should be called when the user selects an item at position
    \a index from the list.
    The selection is forwarded to the input method for further processing.
*/
/*!
    This method should be called when the user selects an item at position
    \a index from the list.
    The selection is forwarded to the input method for further processing.
*/
void DeclarativeSelectionListModel::selectItem(int index)
{
    Q_D(DeclarativeSelectionListModel);
    if (index >= 0 && index < d->rowCount && d->dataSource) {
        emit itemSelected(index);
        d->dataSource->selectionListItemSelected(d->type, index);
    }
}

/*!
 * \internal
 */
QVariant DeclarativeSelectionListModel::itemData(int index, int role) const
{
    return data(this->index(index, 0), role);
}

/*!
    \internal
*/
void DeclarativeSelectionListModel::selectionListChanged(int type)
{
    Q_D(DeclarativeSelectionListModel);
    if (static_cast<Type>(type) == d->type) {
        int oldCount = d->rowCount;
        int newCount = d->dataSource ? d->dataSource->selectionListItemCount(d->type) : 0;
        if (newCount) {
            int changedCount = qMin(oldCount, newCount);
            if (changedCount)
                dataChanged(index(0), index(changedCount - 1));
            if (oldCount > newCount) {
                beginRemoveRows(QModelIndex(), newCount, oldCount - 1);
                d->rowCount = newCount;
                endRemoveRows();
            } else if (oldCount < newCount) {
                beginInsertRows(QModelIndex(), oldCount, newCount - 1);
                d->rowCount = newCount;
                endInsertRows();
            }
        } else {
            beginResetModel();
            d->rowCount = 0;
            endResetModel();
        }
    }
}

/*!
    \internal
*/
void DeclarativeSelectionListModel::selectionListActiveItemChanged(int type, int index)
{
    Q_D(DeclarativeSelectionListModel);
    if (static_cast<Type>(type) == d->type) {
        emit activeItemChanged(index);
    }
}

/*!
    \qmlsignal void SelectionListModel::activeItemChanged(int index)

    This signal is emitted when the active item in the list changes. The
    UI should react to this signal by highlighting the item at \a index in
    the list.
*/
/*!
    \fn void DeclarativeSelectionListModel::activeItemChanged(int index)

    This signal is emitted when the active item in the list changes. The
    UI should react to this signal by highlighting the item at \a index in
    the list.
*/

/*!
    \qmlsignal void SelectionListModel::itemSelected(int index)

    This signal is emitted when an item at \a index is selected by the user.
*/
/*!
    \fn void DeclarativeSelectionListModel::itemSelected(int index)

    This signal is emitted when an item at \a index is selected by the user.
*/
