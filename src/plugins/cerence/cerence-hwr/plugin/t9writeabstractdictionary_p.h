/****************************************************************************
**
** Copyright (C) 2022 The Qt Company Ltd.
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
******************************************************************************/

#ifndef T9WRITEABSTRACTDICTIONARY_P_H
#define T9WRITEABSTRACTDICTIONARY_P_H

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

#include <QtGlobal>

QT_BEGIN_NAMESPACE
namespace QtVirtualKeyboard {

class T9WriteAbstractDictionary
{
    Q_DISABLE_COPY(T9WriteAbstractDictionary)

protected:
    T9WriteAbstractDictionary() {}

public:
    virtual ~T9WriteAbstractDictionary() {}

    virtual bool load() = 0;
    virtual bool create(qint64 createSize) { Q_UNUSED(createSize) return false; }
    virtual void close() {}
    virtual bool convert() { return false; }
    virtual QString name() const = 0;
    virtual const void *data() const = 0;
    virtual qint64 size() const = 0;
    bool isCompleted() const { return state > 0; }

private:
    friend class T9WriteDictionaryTask;
    QAtomicInt state;
};

} // namespace QtVirtualKeyboard
QT_END_NAMESPACE

#endif // T9WRITEABSTRACTDICTIONARY_P_H
