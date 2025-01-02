// Copyright (C) 2021 The Qt Company Ltd.
// SPDX-License-Identifier: LicenseRef-Qt-Commercial OR GPL-3.0-only

#ifndef T9WRITEDICTIONARY_P_H
#define T9WRITEDICTIONARY_P_H

//
//  W A R N I N G
//  -------------
//
// This file is not part of the Qt API.  It exists purely as an
// implementation detail.  This header file may change from version to
// version without notice, or even be removed.
//
// We mean it.
//

#include "t9writeabstractdictionary_p.h"
#include <QFile>
#include <QSharedPointer>
#include "cerence_hwr_p.h"

QT_BEGIN_NAMESPACE
namespace QtVirtualKeyboard {

class T9WriteAbstractSource : public T9WriteAbstractDictionary
{
public:
    T9WriteAbstractSource(const DECUMA_SRC_DICTIONARY_INFO &info);
    virtual ~T9WriteAbstractSource();

    const DECUMA_SRC_DICTIONARY_INFO *info() const;

private:
    const DECUMA_SRC_DICTIONARY_INFO _info;
};

class T9WriteFileSource : public T9WriteAbstractSource
{
public:
    T9WriteFileSource(const DECUMA_SRC_DICTIONARY_INFO &info, const QString &fileName);

    bool load() override;
    bool create(qint64 createSize) override;
    void close() override;

    QString name() const override;
    const void *data() const override;
    qint64 size() const override;

private:
    QFile file;
    void *_data;
    qint64 _size;
};

class T9WriteStringSource : public T9WriteAbstractSource
{
public:
    T9WriteStringSource(const DECUMA_SRC_DICTIONARY_INFO &info, const QStringList &source, const QString &name);

    bool load() override;
    QString name() const override;
    const void *data() const override;
    qint64 size() const override;

private:
    QStringList source;
    QString _data;
    QString _name;
};

class T9WriteDictionary : public T9WriteAbstractDictionary
{
    Q_DISABLE_COPY(T9WriteDictionary)
public:
    explicit T9WriteDictionary(QSharedPointer<T9WriteAbstractSource> source, DECUMA_SESSION *decumaSession, const DECUMA_MEM_FUNCTIONS &memFuncs, bool cjk);
    ~T9WriteDictionary() override;

    bool load() override;
    bool convert() override;
    QString name() const override;
    const void *data() const override;
    qint64 size() const override;

private:
    QSharedPointer<T9WriteAbstractSource> source;
    DECUMA_SESSION *decumaSession;
    const DECUMA_MEM_FUNCTIONS &memFuncs;
    bool cjk;
    void *convertedData;
    DECUMA_UINT32 convertedSize;
};

class T9WriteDynamicDictionary : public T9WriteAbstractDictionary
{
    Q_DISABLE_COPY(T9WriteDynamicDictionary)
public:
    explicit T9WriteDynamicDictionary(QSharedPointer<T9WriteAbstractSource> source, int maxWords, const DECUMA_MEM_FUNCTIONS &memFuncs, bool cjk);
    ~T9WriteDynamicDictionary() override;

    bool load() override;
    QString name() const override;
    const void *data() const override;
    qint64 size() const override;
    qint64 bufferSize() const;

    void save();
    bool hasWord(const QString &word);
    bool removeWord(const QString &word);

private:
    QSharedPointer<T9WriteAbstractSource> source;
    const DECUMA_MEM_FUNCTIONS &memFuncs;
    const bool cjk;
    DECUMA_DYNAMIC_DICTIONARY *_data;
};

} // namespace QtVirtualKeyboard
QT_END_NAMESPACE

#endif // T9WRITEDICTIONARY_P_H
