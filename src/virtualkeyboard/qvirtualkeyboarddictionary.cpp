// Copyright (C) 2021 The Qt Company Ltd.
// SPDX-License-Identifier: LicenseRef-Qt-Commercial OR GPL-3.0-only

#include <QtVirtualKeyboard/qvirtualkeyboarddictionary.h>

/*!
    \class QVirtualKeyboardDictionary

    \inmodule QtVirtualKeyboard
    \ingroup qtvirtualkeyboard-cpp-for-apps

    \brief An application-defined dictionary for virtual keyboard input methods.

    This class defines a named dictionary that consists of words or phrases. The
    dictionary can be enabled in the desired context and its usage depends on
    the current input method of the virtual keyboard.
*/

QVirtualKeyboardDictionary::QVirtualKeyboardDictionary(const QString &name, QObject *parent) :
    QObject(parent),
    _name(name)
{

}

QString QVirtualKeyboardDictionary::name() const
{
    return _name;
}

QStringList QVirtualKeyboardDictionary::contents() const
{
    return _wordList;
}

void QVirtualKeyboardDictionary::setContents(const QStringList &wordList)
{
    if (_wordList != wordList) {
        _wordList = wordList;
        emit contentsChanged();
    }
}

/*!
    \property QVirtualKeyboardDictionary::name
    \brief name of the dictionary.

    This property holds the name of the dictionary that was specified when
    the dictionary was created. The name is necessary when referring to a
    specific dictionary (for example when you activate it in the input context).

    \note The dictionary name cannot be changed later.
*/

/*!
    \property QVirtualKeyboardDictionary::contents
    \brief contents of the dictionary.

    This property holds the contents of the dictionary. Typically, the content
    consists of words or phrases. Note that the dictionary is language neutral,
    meaning it is the application's responsibility to localize the dictionary if
    it contains language-dependent data.

    The content can be set at any time, although it makes sense to set it when
    the input method is not active.
*/

QT_BEGIN_NAMESPACE

QT_END_NAMESPACE
