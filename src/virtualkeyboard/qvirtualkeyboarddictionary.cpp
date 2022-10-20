/****************************************************************************
**
** Copyright (C) 2021 The Qt Company Ltd.
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

#include <QtVirtualKeyboard/qvirtualkeyboarddictionary.h>

/*!
    \class QVirtualKeyboardDictionary

    \inmodule QtVirtualKeyboard

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
