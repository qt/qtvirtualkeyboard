// Copyright (C) 2016 The Qt Company Ltd.
// SPDX-License-Identifier: LicenseRef-Qt-Commercial OR GPL-3.0-only
// Qt-Security score:significant reason:default

#pragma once

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
    int chooseCandidate(int index);
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
