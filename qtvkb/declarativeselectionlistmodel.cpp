/****************************************************************************
**
** Copyright (C) 2013 Digia Plc
** All rights reserved.
** For any questions to Digia, please use contact form at http://qt.digia.com
**
** This file is part of the Qt Quick Enterprise Controls add-on.
**
** Licensees holding valid Qt Enterprise licenses may use this file in
** accordance with the Qt Enterprise License Agreement provided with the
** Software or, alternatively, in accordance with the terms contained in
** a written agreement between you and Digia.
**
** If you have questions regarding the use of this file, please use
** contact form at http://qt.digia.com
**
****************************************************************************/

#include "declarativeselectionlistmodel.h"
#include "abstractinputmethod.h"

class DeclarativeSelectionListModelPrivate
{
public:
    QHash<int, QByteArray> roles;
    AbstractInputMethod *dataSource;
    DeclarativeSelectionListModel::Type type;
    int rowCount;
};

/*!
    \qmltype SelectionListModel
    \instantiates DeclarativeSelectionListModel
    \inqmlmodule QtVkb 1.0
    \brief Provides a data model for the selection lists.

    This type acts as a bridge between the UI and the
    input method that provides the data for selection
    lists.

    An instance of this type can be assigned to a
    ListView::model.

    The following data is made available for the list
    delegate:
    \list
        \li \c "display" Display text for item
        \li \c "wordCompletionLength" Word completion length for item
    \endlist

    The UI must bind to the SelectionListModel::activeItemChanged
    signal and update the highlighted item in the view.

    When the user selects an item from the list, the UI must invoke the
    SelectionListModel::itemSelected() method.
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
    QAbstractListModel(parent),
    d_ptr(new DeclarativeSelectionListModelPrivate())
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
    d->dataSource = dataSource;
    d->type = type;
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

/*!
    The UI invokes this method when user selects an item
    identified by \a index from the selection list.
*/
void DeclarativeSelectionListModel::itemSelected(int index)
{
    Q_D(DeclarativeSelectionListModel);
    if (d->dataSource) {
        d->dataSource->selectionListItemSelected(d->type, index);
    }
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
    \fn void DeclarativeSelectionListModel::activeItemChanged(int index)

    This signal is emitted when the active item in the list changes. The
    UI should react to this signal by highlighting the item at \a index in
    the list.
*/
