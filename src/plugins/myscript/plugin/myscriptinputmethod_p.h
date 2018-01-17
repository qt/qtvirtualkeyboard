/****************************************************************************
**
** Copyright (C) MyScript. Contact: https://www.myscript.com/about/contact-us/sales-inquiry/
** Copyright (C) 2017 Klaralvdalens Datakonsult AB (KDAB). Contact: https://www.qt.io/licensing/
** Copyright (C) 2017 The Qt Company Ltd.
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

#ifndef MYSCRIPTINPUTMETHOD_P_H
#define MYSCRIPTINPUTMETHOD_P_H

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

#include <QtVirtualKeyboard/abstractinputmethod.h>

QT_BEGIN_NAMESPACE
namespace QtVirtualKeyboard {

class MyScriptInputMethodPrivate;

class MyScriptInputMethod : public AbstractInputMethod
{
    Q_OBJECT
    Q_DECLARE_PRIVATE(MyScriptInputMethod)
    Q_PROPERTY(bool superimposed READ superimposed CONSTANT)
public:
    explicit MyScriptInputMethod(QObject *parent = nullptr);
    ~MyScriptInputMethod();

    QList<InputEngine::InputMode> inputModes(const QString &locale) override;
    bool setInputMode(const QString &locale, InputEngine::InputMode inputMode) override;
    bool setTextCase(InputEngine::TextCase textCase) override;

    bool keyEvent(Qt::Key key, const QString &text, Qt::KeyboardModifiers modifiers) override;

    void reset() override;
    void update() override;

    QList<SelectionListModel::Type> selectionLists() override;
    int selectionListItemCount(SelectionListModel::Type type) override;
    QVariant selectionListData(SelectionListModel::Type type, int index, int role) override;
    void selectionListItemSelected(SelectionListModel::Type type, int index) override;

    QList<InputEngine::PatternRecognitionMode> patternRecognitionModes() const override;
    Trace *traceBegin(int traceId, InputEngine::PatternRecognitionMode patternRecognitionMode,
                      const QVariantMap &traceCaptureDeviceInfo, const QVariantMap &traceScreenInfo) override;
    bool traceEnd(Trace *trace) override;

    bool clickPreeditText(int cursorPosition) override;

    bool superimposed() const { return true; }

protected:
    void timerEvent(QTimerEvent *timerEvent) override;

Q_SIGNALS:
    void preeditTextChanged(QString label, bool isCommitted, int cursorPosition, int highlightStart, int highlightEnd);
    void recognitionCommitted(const int gestureType);
    void gestureDetected(const int gestureType, const int gestureCount);

protected Q_SLOTS:
    void setPreeditText(QString label, bool isCommitted, int cursorPosition = -1, int highlightStart = 0, int highlightLength = 0);
    void doGestureAction(const int gestureType, const int gestureCount);

private:
    QScopedPointer<MyScriptInputMethodPrivate> d_ptr;
};

} // namespace QtVirtualKeyboard
QT_END_NAMESPACE

#endif
