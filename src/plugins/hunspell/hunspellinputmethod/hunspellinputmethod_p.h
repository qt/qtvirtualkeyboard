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

#ifndef HUNSPELLINPUTMETHOD_P_H
#define HUNSPELLINPUTMETHOD_P_H

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

#include <QtVirtualKeyboard/qvirtualkeyboardabstractinputmethod.h>
#include <QtHunspellInputMethod/qhunspellinputmethod_global.h>

QT_BEGIN_NAMESPACE
namespace QtVirtualKeyboard {

class HunspellInputMethodPrivate;
class HunspellWordList;

class QHUNSPELLINPUTMETHOD_EXPORT HunspellInputMethod : public QVirtualKeyboardAbstractInputMethod
{
    Q_OBJECT
    Q_DECLARE_PRIVATE(HunspellInputMethod)
protected:
    HunspellInputMethod(HunspellInputMethodPrivate *d_ptr, QObject *parent);
public:
    explicit HunspellInputMethod(QObject *parent = nullptr);
    ~HunspellInputMethod();

    QList<QVirtualKeyboardInputEngine::InputMode> inputModes(const QString &locale) override;
    bool setInputMode(const QString &locale, QVirtualKeyboardInputEngine::InputMode inputMode) override;
    bool setTextCase(QVirtualKeyboardInputEngine::TextCase textCase) override;

    bool keyEvent(Qt::Key key, const QString &text, Qt::KeyboardModifiers modifiers) override;

    QList<QVirtualKeyboardSelectionListModel::Type> selectionLists() override;
    int selectionListItemCount(QVirtualKeyboardSelectionListModel::Type type) override;
    QVariant selectionListData(QVirtualKeyboardSelectionListModel::Type type, int index,
                               QVirtualKeyboardSelectionListModel::Role role) override;
    void selectionListItemSelected(QVirtualKeyboardSelectionListModel::Type type, int index) override;
    bool selectionListRemoveItem(QVirtualKeyboardSelectionListModel::Type type, int index) override;

    bool reselect(int cursorPosition, const QVirtualKeyboardInputEngine::ReselectFlags &reselectFlags) override;

    void reset() override;
    void update() override;

protected Q_SLOTS:
    void updateSuggestions(const QSharedPointer<HunspellWordList> &wordList, int tag);
    void dictionaryLoadCompleted(bool success);

protected:
    QScopedPointer<HunspellInputMethodPrivate> d_ptr;
};

} // namespace QtVirtualKeyboard
QT_END_NAMESPACE

#endif // HUNSPELLINPUTMETHOD_P_H
