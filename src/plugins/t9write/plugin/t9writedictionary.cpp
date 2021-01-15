/****************************************************************************
**
** Copyright (C) 2021 The Qt Company Ltd.
** Contact: https://www.qt.io/licensing/
**
** This file is part of the Qt Virtual Keyboard module of the Qt Toolkit.
**
** $QT_BEGIN_LICENSE:COMM$
**
** Commercial License Usage
** Licensees holding valid commercial Qt licenses may use this file in
** accordance with the commercial license agreement provided with the
** Software or, alternatively, in accordance with the terms contained in
** a written agreement between you and The Qt Company. For licensing terms
** and conditions see https://www.qt.io/terms-conditions. For further
** information use the contact form at https://www.qt.io/contact-us.
**
** $QT_END_LICENSE$
**
**
**
**
**
**
**
**
**
****************************************************************************/

#include "t9writedictionary_p.h"
#include <QLoggingCategory>

QT_BEGIN_NAMESPACE
namespace QtVirtualKeyboard {

Q_DECLARE_LOGGING_CATEGORY(lcT9Write)

T9WriteDictionary::T9WriteDictionary(DECUMA_SESSION *decumaSession,
                                     const DECUMA_MEM_FUNCTIONS &memFuncs,
                                     bool cjk) :
    decumaSession(decumaSession),
    memFuncs(memFuncs),
    cjk(cjk),
    sourceData(nullptr),
    sourceSize(0),
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

bool T9WriteDictionary::load(const QString &fileName)
{
    if (sourceData || convertedData)
        return false;

    file.setFileName(fileName);
    if (file.open(QIODevice::ReadOnly)) {
        sourceSize = file.size();
        sourceData = file.map(0, sourceSize, QFile::NoOptions);
        if (!sourceData) {
            sourceSize = 0;
            qCWarning(lcT9Write) << "Could not read dictionary file" << fileName;
        }
        file.close();
    } else {
        qCWarning(lcT9Write) << "Could not open dictionary file" << fileName;
    }

    return sourceData != nullptr;
}

bool T9WriteDictionary::convert(const DECUMA_SRC_DICTIONARY_INFO &dictionaryInfo)
{
    if (!sourceData || convertedData)
        return false;

    DECUMA_STATUS status;
    status = DECUMA_API(ConvertDictionary)(&convertedData, sourceData, (DECUMA_UINT32)sourceSize,
                                           &dictionaryInfo, &convertedSize, &memFuncs);

    if (status != decumaNoError) {
        qCWarning(lcT9Write) << "Could not convert dictionary" << file.fileName();
        file.unmap((uchar *)sourceData);
        sourceSize = 0;
        sourceData = nullptr;
    }

    return status == decumaNoError;
}

QString T9WriteDictionary::fileName() const
{
    return file.fileName();
}

const void *T9WriteDictionary::data() const
{
    return convertedData ? convertedData : sourceData;
}

qint64 T9WriteDictionary::size() const
{
    return convertedData ? convertedSize : sourceSize;
}

bool T9WriteDictionary::isConverted() const
{
    return convertedData != nullptr;
}

} // namespace QtVirtualKeyboard
QT_END_NAMESPACE
