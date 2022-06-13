// Copyright (C) 2021 The Qt Company Ltd.
// SPDX-License-Identifier: LicenseRef-Qt-Commercial OR GPL-3.0-only

#ifndef XT9AWIME_H
#define XT9AWIME_H

#include "xt9ime.h"

QT_BEGIN_NAMESPACE
namespace QtVirtualKeyboard {

class Xt9AwIme : public Xt9Ime
{
public:
    Xt9AwIme(Xt9RequestCallback *requestCallback, Xt9KeyboardGenerator::CodeConverter *codeConverter = nullptr);

    void sysInit() override;
    bool ldbInit(ET9U32 dwFirstLdbNum, ET9U32 dwSecondLdbNum = ET9PLIDNone, ET9U32 eInputMode = 0) override;
    void setLdbEnabled(bool enabled);
    qint64 dlmPreferredSize() const override;
    bool dlmInit(void *data, qint64 size) override;

    QStringList buildSelectionList(int *defaultListIndex, ET9U16 *gestureValue, ET9STATUS &eStatus) override;
    void selectWord(int index, bool isUserExplicitChoice);

    void noteWordDone(const QString &word);

private:
    static ET9STATUS ET9AWLdbReadData(ET9AWLingInfo *pLingInfo, ET9U8 *ET9FARDATA *ppbSrc, ET9U32 *pdwSizeInBytes);

public:
    ET9AWLingInfo sLingInfo;
    ET9AWLingCmnInfo sLingCmnInfo;
};

} // namespace QtVirtualKeyboard
QT_END_NAMESPACE

#endif // XT9AWIME_H
