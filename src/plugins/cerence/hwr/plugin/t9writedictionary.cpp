// Copyright (C) 2021 The Qt Company Ltd.
// SPDX-License-Identifier: LicenseRef-Qt-Commercial OR GPL-3.0-only

#include "t9writedictionary_p.h"
#include <QLoggingCategory>

QT_BEGIN_NAMESPACE
namespace QtVirtualKeyboard {

Q_DECLARE_LOGGING_CATEGORY(lcT9Write)

// T9WriteAbstractSource

T9WriteAbstractSource::T9WriteAbstractSource(const DECUMA_SRC_DICTIONARY_INFO &info) :
    _info(info)
{
}

T9WriteAbstractSource::~T9WriteAbstractSource()
{
}

const DECUMA_SRC_DICTIONARY_INFO *T9WriteAbstractSource::info() const
{
    return &_info;
}

// T9WriteFileSource

T9WriteFileSource::T9WriteFileSource(const DECUMA_SRC_DICTIONARY_INFO &info, const QString &fileName) :
    T9WriteAbstractSource(info),
    file(fileName),
    _data(nullptr),
    _size(0)
{
}

bool T9WriteFileSource::load()
{
    if (!_data) {
        if (file.open(QIODevice::ReadOnly)) {
            _size = file.size();
            _data = file.map(0, _size, QFile::NoOptions);
            if (!_data) {
                _size = 0;
                qCWarning(lcT9Write) << "Could not read dictionary file" << file.fileName();
            }
            file.close();
        }
    }

    return _data != nullptr;
}

bool T9WriteFileSource::create(qint64 createSize)
{
    close();

    if (file.open(QIODevice::ReadWrite)) {
        if (file.resize(createSize)) {
            _size = file.size();
            _data = file.map(0, _size, QFile::NoOptions);
            if (!_data) {
                _size = 0;
                qCWarning(lcT9Write) << "Could not read dictionary file" << file.fileName();
            }
        } else {
            qCWarning(lcT9Write) << "Could not resize dictionary file" << file.fileName();
        }
        file.close();
    }

    return _data != nullptr;
}

void T9WriteFileSource::close()
{
    if (_data) {
        file.unmap(static_cast<uchar *>(_data));
        _data = nullptr;
        _size = 0;
    }
}

QString T9WriteFileSource::name() const
{
    return file.fileName();
}

const void *T9WriteFileSource::data() const
{
    return _data;
}

qint64 T9WriteFileSource::size() const
{
    return _size;
}

// T9WriteStringSource

T9WriteStringSource::T9WriteStringSource(const DECUMA_SRC_DICTIONARY_INFO &info, const QStringList &source, const QString &name) :
    T9WriteAbstractSource(info),
    source(source),
    _name(name)
{
}

bool T9WriteStringSource::load()
{
    _data = source.join(QLatin1Char('\r'));
    return true;
}

QString T9WriteStringSource::name() const
{
    return _name;
}

const void *T9WriteStringSource::data() const
{
    return _data.utf16();
}

qint64 T9WriteStringSource::size() const
{
    return _data.size();
}

// T9WriteDictionary

T9WriteDictionary::T9WriteDictionary(QSharedPointer<T9WriteAbstractSource> source,
                                     DECUMA_SESSION *decumaSession,
                                     const DECUMA_MEM_FUNCTIONS &memFuncs,
                                     bool cjk) :
    source(source),
    decumaSession(decumaSession),
    memFuncs(memFuncs),
    cjk(cjk),
    convertedData(nullptr),
    convertedSize(0)
{
}

T9WriteDictionary::~T9WriteDictionary()
{
    if (convertedData) {
        DECUMA_STATUS status = DECUMA_API(DestroyConvertedDictionary)(&convertedData, &memFuncs);
        Q_ASSERT(status == decumaNoError);
        Q_ASSERT(convertedData == nullptr);
    }
}

bool T9WriteDictionary::load()
{
    return source->load();
}

bool T9WriteDictionary::convert()
{
    if (!source->data() || convertedData)
        return false;

    DECUMA_STATUS status;
    status = DECUMA_API(ConvertDictionary)(&convertedData, source->data(), static_cast<DECUMA_UINT32>(source->size()),
                                           source->info(), &convertedSize, &memFuncs);

    if (status != decumaNoError) {
        qCWarning(lcT9Write) << "Could not convert dictionary";
    }

    return status == decumaNoError;
}

QString T9WriteDictionary::name() const
{
    return source->name();
}

const void *T9WriteDictionary::data() const
{
    return convertedData ? convertedData : source->data();
}

qint64 T9WriteDictionary::size() const
{
    return convertedData ? convertedSize : source->size();
}

T9WriteDynamicDictionary::T9WriteDynamicDictionary(QSharedPointer<T9WriteAbstractSource> source, int maxWords, const DECUMA_MEM_FUNCTIONS &memFuncs, bool cjk) :
    source(source),
    memFuncs(memFuncs),
    cjk(cjk),
    _data(nullptr)
{
    DECUMA_API(DynamicDictionaryCreate)(&_data, static_cast<DECUMA_UINT32>(maxWords), &memFuncs);
}

T9WriteDynamicDictionary::~T9WriteDynamicDictionary()
{
    if (_data) {
        DECUMA_API(DynamicDictionaryDestroy)(&_data);
    }
}

bool T9WriteDynamicDictionary::load()
{
    if (!_data)
        return false;

    DECUMA_STATUS status;
    DECUMA_UINT32 nUnprocessedSize = 0;
    if (source->load()) {
        status = DECUMA_API(DynamicDictionaryAddWords)(_data, source->data(), static_cast<DECUMA_UINT32>(source->size()), &nUnprocessedSize);
        if (status) {
            qCWarning(lcT9Write) << "Could not load words to dynamic dictionary, error" << status;
        }
        source->close();
    }

    return true;
}

QString T9WriteDynamicDictionary::name() const
{
    return source->name();
}

const void *T9WriteDynamicDictionary::data() const
{
    return _data;
}

qint64 T9WriteDynamicDictionary::size() const
{
    return 0;
}

qint64 T9WriteDynamicDictionary::bufferSize() const
{
    DECUMA_UINT32 result = 0;
    if (_data)
        DECUMA_API(DynamicDictionaryGetWordsBufferSize)(_data, &result);
    return result;
}

void T9WriteDynamicDictionary::save()
{
    if (_data) {
        DECUMA_UINT32 nWordsWritten = 0;
        DECUMA_UINT32 nBytesWritten = 0;
        qint64 fileSize = bufferSize();
        if (source->create(fileSize)) {
            DECUMA_STATUS status = DECUMA_API(DynamicDictionaryGetWords)(_data, const_cast<void *>(source->data()), static_cast<DECUMA_UINT32>(fileSize), &nWordsWritten, &nBytesWritten);
            source->close();
        }
    }
}

bool T9WriteDynamicDictionary::hasWord(const QString &word)
{
    if (!_data)
        return false;

    int found = 0;
    DECUMA_API(DynamicDictionaryHasWord)(_data, word.utf16(), &found);

    return found != 0;
}

bool T9WriteDynamicDictionary::removeWord(const QString &word)
{
    DECUMA_STATUS status;

    status = DECUMA_API(DynamicDictionaryDeleteWord)(_data, word.utf16());

    return !status;
}

} // namespace QtVirtualKeyboard
QT_END_NAMESPACE
