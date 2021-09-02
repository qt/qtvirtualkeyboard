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

#ifndef XT9CPIME_H
#define XT9CPIME_H

#include "xt9ime.h"

QT_BEGIN_NAMESPACE
namespace QtVirtualKeyboard {

class Xt9CpIme : public Xt9Ime
{
public:
    Xt9CpIme(Xt9RequestCallback *requestCallback);

    static Xt9KeyboardGenerator::CodeConverter *getCangjieConverter();

    void sysInit() override;
    bool ldbInit(ET9U32 dwFirstLdbNum, ET9U32 dwSecondLdbNum = ET9PLIDNone, ET9U32 eInputMode = 0) override;
    qint64 dlmPreferredSize() const override;
    bool dlmInit(void *data, qint64 size) override;

    QString exactWord(int *wordCompLen = nullptr) override;
    void replaceSpecialSymbol(QString &exactWord) const;
    QString spell();
    QStringList buildSelectionList(int *defaultListIndex, ET9U16 *gestureValue, ET9STATUS &eStatus) override;
    ET9STATUS selectWord(int index);

    void cursorMoved() override;

    void commitSelection();

    ET9SYMB lastSymb();
    bool addTone(ET9CPSYMB symb);

private:
    static ET9STATUS ET9CPLdbReadData(ET9CPLingInfo *pLingInfo, ET9U8 *ET9FARDATA *ppbSrc, ET9U32 *pdwSizeInBytes);

public:
    ET9CPLingInfo sLingInfo;
};

} // namespace QtVirtualKeyboard
QT_END_NAMESPACE

#endif // XT9CPIME_H
