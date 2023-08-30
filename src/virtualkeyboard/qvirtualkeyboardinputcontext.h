// Copyright (C) 2016 The Qt Company Ltd.
// SPDX-License-Identifier: LicenseRef-Qt-Commercial OR GPL-3.0-only

#ifndef QVIRTUALKEYBOARDINPUTCONTEXT_H
#define QVIRTUALKEYBOARDINPUTCONTEXT_H

#include <QtCore/QObject>
#include <QtCore/QRectF>
#include <QtCore/QLocale>
#include <QtGui/QInputMethodEvent>
#include <QtGui/QInputMethod>
#include <QtQml/qqml.h>
#include <QtVirtualKeyboard/qvirtualkeyboard_global.h>

QT_BEGIN_NAMESPACE

namespace QtVirtualKeyboard {
class PlatformInputContext;
}
class QVirtualKeyboardInputEngine;
class QVirtualKeyboardInputContextPrivate;
class QVirtualKeyboardObserver;

class Q_VIRTUALKEYBOARD_EXPORT QVirtualKeyboardInputContext : public QObject
{
    Q_OBJECT
    Q_DISABLE_COPY(QVirtualKeyboardInputContext)
    Q_DECLARE_PRIVATE(QVirtualKeyboardInputContext)
    Q_PROPERTY(bool shift READ isShiftActive NOTIFY shiftActiveChanged)
    Q_PROPERTY(bool shiftActive READ isShiftActive NOTIFY shiftActiveChanged REVISION(2, 4))
    Q_PROPERTY(bool capsLock READ isCapsLockActive NOTIFY capsLockActiveChanged)
    Q_PROPERTY(bool capsLockActive READ isCapsLockActive NOTIFY capsLockActiveChanged REVISION(2, 4))
    Q_PROPERTY(bool uppercase READ isUppercase NOTIFY uppercaseChanged)
    Q_PROPERTY(int anchorPosition READ anchorPosition NOTIFY anchorPositionChanged)
    Q_PROPERTY(int cursorPosition READ cursorPosition NOTIFY cursorPositionChanged)
    Q_PROPERTY(Qt::InputMethodHints inputMethodHints READ inputMethodHints NOTIFY inputMethodHintsChanged)
    Q_PROPERTY(QString preeditText READ preeditText WRITE setPreeditText NOTIFY preeditTextChanged)
    Q_PROPERTY(QString surroundingText READ surroundingText NOTIFY surroundingTextChanged)
    Q_PROPERTY(QString selectedText READ selectedText NOTIFY selectedTextChanged)
    Q_PROPERTY(QRectF anchorRectangle READ anchorRectangle NOTIFY anchorRectangleChanged)
    Q_PROPERTY(QRectF cursorRectangle READ cursorRectangle NOTIFY cursorRectangleChanged)
    Q_PROPERTY(bool animating READ isAnimating WRITE setAnimating NOTIFY animatingChanged)
    Q_PROPERTY(QString locale READ locale NOTIFY localeChanged)
    Q_PROPERTY(QObject *inputItem READ inputItem NOTIFY inputItemChanged)
    Q_PROPERTY(QVirtualKeyboardInputEngine *inputEngine READ inputEngine CONSTANT)
    Q_PROPERTY(bool selectionControlVisible READ isSelectionControlVisible NOTIFY selectionControlVisibleChanged)
    Q_PROPERTY(bool anchorRectIntersectsClipRect READ anchorRectIntersectsClipRect NOTIFY anchorRectIntersectsClipRectChanged)
    Q_PROPERTY(bool cursorRectIntersectsClipRect READ cursorRectIntersectsClipRect NOTIFY cursorRectIntersectsClipRectChanged)
    Q_PROPERTY(QVirtualKeyboardInputContextPrivate *priv READ priv CONSTANT REVISION(2, 0))
    Q_PROPERTY(QVirtualKeyboardObserver *keyboardObserver READ keyboardObserver CONSTANT REVISION(6, 1))
    Q_MOC_INCLUDE("qvirtualkeyboardinputengine.h")
    Q_MOC_INCLUDE("qvirtualkeyboardinputcontext_p.h")

    // The QML macros are unused for now, until we can move the QML_NAMED_ELEMENT back here.
    // QML_SINGLETON generates some code that might or might not emit symbols on some platforms.
    QML_SINGLETON
    QML_ADDED_IN_VERSION(1, 0)
    QML_EXTRA_VERSION(2, 0)

public:
    explicit QVirtualKeyboardInputContext(QObject *parent = nullptr);
    ~QVirtualKeyboardInputContext();

    bool isShiftActive() const;
    bool isCapsLockActive() const;
    bool isUppercase() const;
    int anchorPosition() const;
    int cursorPosition() const;
    Qt::InputMethodHints inputMethodHints() const;
    QString preeditText() const;
    void setPreeditText(const QString &text, QList<QInputMethodEvent::Attribute> attributes = QList<QInputMethodEvent::Attribute>(), int replaceFrom = 0, int replaceLength = 0);
    QList<QInputMethodEvent::Attribute> preeditTextAttributes() const;
    QString surroundingText() const;
    QString selectedText() const;
    QRectF anchorRectangle() const;
    QRectF cursorRectangle() const;
    bool isAnimating() const;
    void setAnimating(bool isAnimating);
    QString locale() const;
    QObject *inputItem() const;
    QVirtualKeyboardInputEngine *inputEngine() const;
    bool isSelectionControlVisible() const;
    bool anchorRectIntersectsClipRect() const;
    bool cursorRectIntersectsClipRect() const;
    QVirtualKeyboardInputContextPrivate *priv() const;
    QVirtualKeyboardObserver *keyboardObserver() const;

    Q_INVOKABLE void sendKeyClick(int key, const QString &text, int modifiers = 0);
    Q_INVOKABLE void commit();
    Q_INVOKABLE void commit(const QString &text, int replaceFrom = 0, int replaceLength = 0);
    Q_INVOKABLE void clear();

    // For selection handles
    Q_INVOKABLE void setSelectionOnFocusObject(const QPointF &anchorPos, const QPointF &cursorPos);

Q_SIGNALS:
    void preeditTextChanged();
    void inputMethodHintsChanged();
    void surroundingTextChanged();
    void selectedTextChanged();
    void anchorPositionChanged();
    void cursorPositionChanged();
    void anchorRectangleChanged();
    void cursorRectangleChanged();
    void shiftActiveChanged();
    void capsLockActiveChanged();
    void uppercaseChanged();
    void animatingChanged();
    void localeChanged();
    void inputItemChanged();
    void selectionControlVisibleChanged();
    void anchorRectIntersectsClipRectChanged();
    void cursorRectIntersectsClipRectChanged();

private:

    QScopedPointer<QVirtualKeyboardInputContextPrivate> d_ptr;
};

QT_END_NAMESPACE

#endif
