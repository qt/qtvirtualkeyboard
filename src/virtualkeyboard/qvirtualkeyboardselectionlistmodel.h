// Copyright (C) 2016 The Qt Company Ltd.
// SPDX-License-Identifier: LicenseRef-Qt-Commercial OR GPL-3.0-only

#ifndef QVIRTUALKEYBOARDSELECTIONLISTMODEL_H
#define QVIRTUALKEYBOARDSELECTIONLISTMODEL_H

#include <QtCore/QAbstractListModel>
#include <QtQml/qqml.h>
#include <QtVirtualKeyboard/qvirtualkeyboard_global.h>

QT_BEGIN_NAMESPACE

class QVirtualKeyboardAbstractInputMethod;
class QVirtualKeyboardInputEngine;
class QVirtualKeyboardSelectionListModelPrivate;

class Q_VIRTUALKEYBOARD_EXPORT QVirtualKeyboardSelectionListModel : public QAbstractListModel
{
    Q_OBJECT
    Q_DECLARE_PRIVATE(QVirtualKeyboardSelectionListModel)
    Q_PROPERTY(int count READ count NOTIFY countChanged)
    QML_NAMED_ELEMENT(SelectionListModel)
    QML_UNCREATABLE("SelectionListModel is only available via InputEngine.wordCandidateListModel")
    QML_ADDED_IN_VERSION(1, 0)
    QML_EXTRA_VERSION(2, 0)

    explicit QVirtualKeyboardSelectionListModel(QObject *parent = nullptr);

public:
    enum class Type
    {
        WordCandidateList = 0
    };
    Q_ENUM(Type)

    enum class Role
    {
        Display = Qt::DisplayRole,
        DisplayRole = Display,
        WordCompletionLength = Qt::UserRole + 1,
        WordCompletionLengthRole = WordCompletionLength,
        Dictionary,
        CanRemoveSuggestion
    };
    Q_ENUM(Role)

    enum class DictionaryType
    {
        Default = 0,
        User
    };
    Q_ENUM(DictionaryType)

    ~QVirtualKeyboardSelectionListModel();
    void setDataSource(QVirtualKeyboardAbstractInputMethod *dataSource, Type type);
    QVirtualKeyboardAbstractInputMethod *dataSource() const;
    int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;
    QHash<int,QByteArray> roleNames() const override;

    int count() const;

    Q_INVOKABLE void selectItem(int index);
    Q_INVOKABLE void removeItem(int index);
    Q_INVOKABLE QVariant dataAt(int index, Role role = Role::Display) const;

Q_SIGNALS:
    void countChanged();
    void activeItemChanged(int index);
    void itemSelected(int index);

protected Q_SLOTS:
    void selectionListChanged(Type type);
    void selectionListActiveItemChanged(Type type, int index);
    void dataSourceDestroyed();

private:
    friend class QVirtualKeyboardInputEngine;
};

QT_END_NAMESPACE

Q_DECLARE_METATYPE(QVirtualKeyboardSelectionListModel::Type)
Q_DECLARE_METATYPE(QVirtualKeyboardSelectionListModel::Role)
Q_DECLARE_METATYPE(QVirtualKeyboardSelectionListModel::DictionaryType)

#endif // QVIRTUALKEYBOARDSELECTIONLISTMODEL_H
