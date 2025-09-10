// Copyright (C) 2016 The Qt Company Ltd.
// SPDX-License-Identifier: LicenseRef-Qt-Commercial OR GPL-3.0-only

#ifndef QVIRTUALKEYBOARDINPUTENGINE_H
#define QVIRTUALKEYBOARDINPUTENGINE_H

#include <QtCore/QObject>
#include <QtCore/QPointer>
#include <QtQml/qqml.h>
#include <QtVirtualKeyboard/qvirtualkeyboard_global.h>

QT_BEGIN_NAMESPACE

class QVirtualKeyboardInputContext;
class QVirtualKeyboardSelectionListModel;
class QVirtualKeyboardAbstractInputMethod;
class QVirtualKeyboardInputEnginePrivate;
class QVirtualKeyboardTrace;

class Q_VIRTUALKEYBOARD_EXPORT QVirtualKeyboardInputEngine : public QObject
{
    Q_OBJECT
    Q_DISABLE_COPY(QVirtualKeyboardInputEngine)
    Q_DECLARE_PRIVATE(QVirtualKeyboardInputEngine)
    Q_PROPERTY(Qt::Key activeKey READ activeKey NOTIFY activeKeyChanged)
    Q_PROPERTY(Qt::Key previousKey READ previousKey NOTIFY previousKeyChanged)
    Q_PROPERTY(QVirtualKeyboardAbstractInputMethod *inputMethod READ inputMethod WRITE setInputMethod NOTIFY inputMethodChanged)
    Q_PROPERTY(QList<int> inputModes READ inputModes NOTIFY inputModesChanged)
    Q_PROPERTY(InputMode inputMode READ inputMode WRITE setInputMode NOTIFY inputModeChanged)
    Q_PROPERTY(QList<int> patternRecognitionModes READ patternRecognitionModes NOTIFY patternRecognitionModesChanged)
    Q_PROPERTY(QVirtualKeyboardSelectionListModel *wordCandidateListModel READ wordCandidateListModel NOTIFY wordCandidateListModelChanged)
    Q_PROPERTY(bool wordCandidateListVisibleHint READ wordCandidateListVisibleHint NOTIFY wordCandidateListVisibleHintChanged)
    Q_MOC_INCLUDE("qvirtualkeyboardabstractinputmethod.h")
    QML_NAMED_ELEMENT(InputEngine)
    QML_UNCREATABLE("InputEngine is only available via InputContext.inputEngine")
    QML_ADDED_IN_VERSION(1, 0)
    QML_EXTRA_VERSION(2, 0)

    explicit QVirtualKeyboardInputEngine(QVirtualKeyboardInputContext *parent = nullptr);
    void init();

public:
    enum class TextCase {
        Lower,
        Upper
    };
    Q_ENUM(TextCase)

    enum class InputMode {
        Latin,
        Numeric,
        Dialable,
        Pinyin,
        Cangjie,
        Zhuyin,
        Hangul,
        Hiragana,
        Katakana,
        FullwidthLatin,
        Greek,
        Cyrillic,
        Arabic,
        Hebrew,
        ChineseHandwriting,
        JapaneseHandwriting,
        KoreanHandwriting,
        Thai,
        Stroke,
        Romaji,
    };
    Q_ENUM(InputMode)

    enum class PatternRecognitionMode {
        None,
        PatternRecognitionDisabled = None,
        Handwriting,
        HandwritingRecoginition = Handwriting
    };
    Q_ENUM(PatternRecognitionMode)

    enum class ReselectFlag {
        WordBeforeCursor = 0x1,
        WordAfterCursor = 0x2,
        WordAtCursor = WordBeforeCursor | WordAfterCursor
    };
    Q_FLAG(ReselectFlag)
    Q_DECLARE_FLAGS(ReselectFlags, ReselectFlag)

public:
    ~QVirtualKeyboardInputEngine();

    Q_INVOKABLE bool virtualKeyPress(Qt::Key key, const QString &text, Qt::KeyboardModifiers modifiers, bool repeat);
    Q_INVOKABLE void virtualKeyCancel();
    Q_INVOKABLE bool virtualKeyRelease(Qt::Key key, const QString &text, Qt::KeyboardModifiers modifiers);
    Q_INVOKABLE bool virtualKeyClick(Qt::Key key, const QString &text, Qt::KeyboardModifiers modifiers);

    QVirtualKeyboardInputContext *inputContext() const;
    Qt::Key activeKey() const;
    Qt::Key previousKey() const;

    QVirtualKeyboardAbstractInputMethod *inputMethod() const;
    void setInputMethod(QVirtualKeyboardAbstractInputMethod *inputMethod);

    QList<int> inputModes() const;

    InputMode inputMode() const;
    void setInputMode(InputMode inputMode);

    QVirtualKeyboardSelectionListModel *wordCandidateListModel() const;
    bool wordCandidateListVisibleHint() const;

    QList<int> patternRecognitionModes() const;
    Q_INVOKABLE QVirtualKeyboardTrace *traceBegin(
            int traceId, PatternRecognitionMode patternRecognitionMode,
            const QVariantMap &traceCaptureDeviceInfo, const QVariantMap &traceScreenInfo);
    Q_INVOKABLE bool traceEnd(QVirtualKeyboardTrace *trace);

    Q_INVOKABLE bool reselect(int cursorPosition, const ReselectFlags &reselectFlags);
    bool clickPreeditText(int cursorPosition);

Q_SIGNALS:
    void virtualKeyClicked(Qt::Key key, const QString &text, Qt::KeyboardModifiers modifiers, bool isAutoRepeat);
    void activeKeyChanged(Qt::Key key);
    void previousKeyChanged(Qt::Key key);
    void inputMethodChanged();
    void inputMethodReset();
    void inputMethodUpdate();
    void inputModesChanged();
    void inputModeChanged();
    void patternRecognitionModesChanged();
    void wordCandidateListModelChanged();
    void wordCandidateListVisibleHintChanged();

private Q_SLOTS:
    void reset();
    void update();
    void shiftChanged();
    void updateSelectionListModels();
    void updateInputModes();

protected:
    void timerEvent(QTimerEvent *timerEvent) override;

private:
    friend class QVirtualKeyboardInputContext;
    friend class QVirtualKeyboardInputContextPrivate;
};

Q_DECL_CONST_FUNCTION Q_DECL_CONSTEXPR inline uint qHash(QVirtualKeyboardInputEngine::InputMode key, uint seed = 0) Q_DECL_NOTHROW { return uint(key) ^ seed; }
Q_DECLARE_OPERATORS_FOR_FLAGS(QVirtualKeyboardInputEngine::ReselectFlags)

QT_END_NAMESPACE

Q_DECLARE_METATYPE(QVirtualKeyboardInputEngine::TextCase)
Q_DECLARE_METATYPE(QVirtualKeyboardInputEngine::InputMode)
Q_DECLARE_METATYPE(QVirtualKeyboardInputEngine::PatternRecognitionMode)
Q_DECLARE_METATYPE(QVirtualKeyboardInputEngine::ReselectFlag)

#endif
