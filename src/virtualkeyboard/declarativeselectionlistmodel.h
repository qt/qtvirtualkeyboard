/****************************************************************************
**
** Copyright (C) 2013 Digia Plc
** All rights reserved.
** For any questions to Digia, please use contact form at http://qt.digia.com
**
** This file is part of the Qt Virtual Keyboard add-on for Qt Enterprise.
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
