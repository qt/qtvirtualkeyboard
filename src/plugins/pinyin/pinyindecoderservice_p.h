// Copyright (C) 2016 The Qt Company Ltd.
// SPDX-License-Identifier: LicenseRef-Qt-Commercial OR GPL-3.0-only

#ifndef PINYINDECODERSERVICE_P_H
#define PINYINDECODERSERVICE_P_H

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

#include <QObject>

QT_BEGIN_NAMESPACE
namespace QtVirtualKeyboard {

class PinyinDecoderService : public QObject
{
    Q_OBJECT
    Q_DISABLE_COPY(PinyinDecoderService)
    explicit PinyinDecoderService(QObject *parent = nullptr);

public:
    ~PinyinDecoderService();

    static PinyinDecoderService *getInstance();

    bool init();
    void setUserDictionary(bool enabled);
    bool isUserDictionaryEnabled() const;
    void setLimits(int maxSpelling, int maxHzsLen);
    int search(const QString &spelling);
    int deleteSearch(int pos, bool isPosInSpellingId, bool clearFixedInThisStep);
    void resetSearch();
    QString pinyinString(bool decoded);
    int pinyinStringLength(bool decoded);
    QList<int> spellingStartPositions();
    QString candidateAt(int index);
    QList<QString> fetchCandidates(int index, int count, int sentFixedLen);
    int chooceCandidate(int index);
    int cancelLastChoice();
    int fixedLength();
    void flushCache();
    QList<QString> predictionList(const QString &history);

private:
    static QScopedPointer<PinyinDecoderService> _instance;
    bool initDone;
};

} // namespace QtVirtualKeyboard
QT_END_NAMESPACE

#endif // PINYINDECODERSERVICE_P_H
