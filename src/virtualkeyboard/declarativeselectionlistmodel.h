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

#ifndef DECLARATIVESELECTIONLISTMODEL_H
#define DECLARATIVESELECTIONLISTMODEL_H

#include <QAbstractListModel>

class AbstractInputMethod;
class DeclarativeInputEngine;
class DeclarativeSelectionListModelPrivate;

class DeclarativeSelectionListModel : public QAbstractListModel
{
    Q_OBJECT
    Q_ENUMS(Type)
    Q_ENUMS(Role)
    Q_DECLARE_PRIVATE(DeclarativeSelectionListModel)

    explicit DeclarativeSelectionListModel(QObject *parent = 0);

public:
    enum Type
    {
        WordCandidateList = 0
    };
    enum Role
    {
        DisplayRole = Qt::DisplayRole,
        WordCompletionLengthRole = Qt::UserRole + 1
    };

    ~DeclarativeSelectionListModel();
    void setDataSource(AbstractInputMethod *dataSource, Type type);
    AbstractInputMethod *dataSource() const;
    int rowCount(const QModelIndex &parent = QModelIndex()) const;
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const;
    QHash<int,QByteArray> roleNames() const;

    Q_INVOKABLE void selectItem(int index);
    Q_INVOKABLE QVariant itemData(int index, int role = Qt::DisplayRole) const;

signals:
    void activeItemChanged(int index);
    void itemSelected(int index);

protected slots:
    void selectionListChanged(int type);
    void selectionListActiveItemChanged(int type, int index);

private:
    friend class DeclarativeInputEngine;
};

Q_DECLARE_METATYPE(DeclarativeSelectionListModel::Type)
Q_DECLARE_METATYPE(DeclarativeSelectionListModel::Role)

#endif // DECLARATIVESELECTIONLISTMODEL_H
