/****************************************************************************
**
** Copyright (C) 2016 The Qt Company Ltd.
** Contact: https://www.qt.io/licensing/
**
** This file is part of the Qt Virtual Keyboard module of the Qt Toolkit.
**
** $QT_BEGIN_LICENSE:GPL$
** Commercial License Usage
** Licensees holding valid commercial Qt licenses may use this file in
** accordance with the commercial license agreement provided with the
** Software or, alternatively, in accordance with the terms contained in
** a written agreement between you and The Qt Company. For licensing terms
** and conditions see https://www.qt.io/terms-conditions. For further
** information use the contact form at https://www.qt.io/contact-us.
**
** GNU General Public License Usage
** Alternatively, this file may be used under the terms of the GNU
** General Public License version 3 or (at your option) any later version
** approved by the KDE Free Qt Foundation. The licenses are as published by
** the Free Software Foundation and appearing in the file LICENSE.GPL3
** included in the packaging of this file. Please review the following
** information to ensure the GNU General Public License requirements will
** be met: https://www.gnu.org/licenses/gpl-3.0.html.
**
** $QT_END_LICENSE$
**
****************************************************************************/

#ifndef T9WRITEINPUTMETHOD_H
#define T9WRITEINPUTMETHOD_H

#include "abstractinputmethod.h"
#include <QSharedPointer>

namespace QtVirtualKeyboard {

class T9WriteInputMethodPrivate;
class T9WriteDictionary;

class T9WriteInputMethod : public AbstractInputMethod
{
    Q_OBJECT
    Q_DECLARE_PRIVATE(T9WriteInputMethod)

public:
    explicit T9WriteInputMethod(QObject *parent = 0);
    ~T9WriteInputMethod();

    QList<InputEngine::InputMode> inputModes(const QString &locale);
    bool setInputMode(const QString &locale, InputEngine::InputMode inputMode);
    bool setTextCase(InputEngine::TextCase textCase);

    bool keyEvent(Qt::Key key, const QString &text, Qt::KeyboardModifiers modifiers);

    void reset();
    void update();

    QList<SelectionListModel::Type> selectionLists();
    int selectionListItemCount(SelectionListModel::Type type);
    QVariant selectionListData(SelectionListModel::Type type, int index, int role);
    void selectionListItemSelected(SelectionListModel::Type type, int index);

    QList<InputEngine::PatternRecognitionMode> patternRecognitionModes() const;
    Trace *traceBegin(int traceId, InputEngine::PatternRecognitionMode patternRecognitionMode,
                      const QVariantMap &traceCaptureDeviceInfo, const QVariantMap &traceScreenInfo);
    bool traceEnd(Trace *trace);

    bool reselect(int cursorPosition, const InputEngine::ReselectFlags &reselectFlags);

signals:
    void resultListChanged();

protected:
    void timerEvent(QTimerEvent *timerEvent);

protected slots:
    void dictionaryLoadCompleted(QSharedPointer<T9WriteDictionary> dictionary);
    void resultsAvailable(const QVariantList &resultList);
    void processResult();
    void recognitionError(int status);
};

}

#endif
