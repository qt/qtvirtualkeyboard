// Copyright (C) 2021 The Qt Company Ltd.
// SPDX-License-Identifier: LicenseRef-Qt-Commercial OR GPL-3.0-only

#include "xt9ldbmanager.h"
#include "xt9dbfile.h"
#include <QDirIterator>
#include <QLibraryInfo>
#include <QMap>
#include <QtVirtualKeyboard/private/settings_p.h>

QT_BEGIN_NAMESPACE
namespace QtVirtualKeyboard {

const QRegularExpression Xt9LdbManager::ldbRegex = QRegularExpression(QStringLiteral("([A-Z]{2})([a-z]{2})(?:UN)(.*?)(?:_xt9_?)?((?:CJI_|HC_|big_)?ALM3?)?(\\.ldb|\\.phd)"));

Xt9LdbManager::Xt9LdbManager() :
    _phdEnabled(false)
{
    QString xt9LdbPath(qEnvironmentVariable("QT_VIRTUALKEYBOARD_XT9_LDB_PATH"));
    const QString pathListSep(
#if defined(Q_OS_WIN32)
        QStringLiteral(";")
#else
        QStringLiteral(":")
#endif
    );
    QStringList userPaths(xt9LdbPath.split(pathListSep, Qt::SkipEmptyParts));
    const QStringList defaultPaths = userPaths
            << QDir(QStringLiteral("%1/qtvirtualkeyboard/cerence/xt9/").arg(QLibraryInfo::path(QLibraryInfo::DataPath))).absolutePath()
            << QLatin1String(":/qt-project.org/imports/QtQuick/VirtualKeyboard/Cerence/Xt9")
               ;
    for (const QString &defaultPath : defaultPaths) {
        addSearchPath(defaultPath);
    }
}

void Xt9LdbManager::addSearchPath(const QString &searchPath)
{
    if (!searchPaths.contains(searchPath))
        searchPaths.append(searchPath);
}

void Xt9LdbManager::setPhdEnabled(bool enabled)
{
    _phdEnabled = enabled;
}

bool Xt9LdbManager::phdEnabled() const
{
    return _phdEnabled;
}

bool Xt9LdbManager::loadDictionary(const QLocale &locale, const void *&data, qint64 &size)
{
    const QString language = locale.name();
    if (ldbMap.contains(language)) {
        QSharedPointer<Xt9DbFile> ldb = ldbMap[language];
        if (_phdEnabled || !ldb->fileName().endsWith(QLatin1String(".phd"), Qt::CaseInsensitive)) {
            data = ldb->roData();
            size = ldb->size();
            return true;
        }
    }

    QString dictionaryFile = findDictionary(locale);
    if (!dictionaryFile.isEmpty()) {
        QSharedPointer<Xt9DbFile> ldb(new Xt9DbFile(dictionaryFile));
        data = ldb->roData();
        size = ldb->size();
        if (data) {
            ldbMap[language] = ldb;
            return true;
        }
    }

    data = nullptr;
    size = 0;

    return false;
}

void Xt9LdbManager::closeAll()
{
    ldbMap.clear();
}

QString Xt9LdbManager::findDictionary(const QLocale &locale) const
{
    QStringList languageCountry = locale.name().split(QLatin1String("_"));
    if (languageCountry.size() != 2)
        return QString();
    const QString language_ISO_639_1 = languageCountry[0].toUpper();
    const QString country = languageCountry[1].toUpper();
    const QLocale::Script script = locale.script();

    QMap<QString, int> matchedDictionaries;
    for (const QString &ldbDirectory : searchPaths) {
        QDirIterator it(ldbDirectory, QDirIterator::NoIteratorFlags);
        while (it.hasNext()) {
            QString fileEntry = it.next();
            const QFileInfo fileInfo(fileEntry);

            if (fileInfo.isDir())
                continue;

            QString fileName(fileInfo.fileName());
            fileName.remove(QRegularExpression(QLatin1String("^zzEval_")));

            QRegularExpressionMatch match = ldbRegex.match(fileName);
            if (!match.hasMatch())
                continue;

            QString xt9Language = match.captured(1);

            // Special case for language codes not following ISO 639-1
            if (xt9Language == QLatin1String("NO"))
                xt9Language = QStringLiteral("NB");

            const QString ext(match.captured(5));
            if (xt9Language == language_ISO_639_1 &&
                    (ext == QLatin1String(".ldb") || (_phdEnabled && ext == QLatin1String(".phd")))) {

                int score = 1;

                QString xt9CountryOrDetail = match.captured(3);
                const QString charsetClassifier = match.captured(2);
                const QString almClassifier = match.captured(4);

                // Special case for country codes not following ISO 639-1
                if (xt9CountryOrDetail == QLatin1String("UK"))
                    xt9CountryOrDetail = QStringLiteral("GB");
                else if (xt9CountryOrDetail == QLatin1String("latam"))
                    xt9CountryOrDetail = QStringLiteral("MX");
                else if (xt9CountryOrDetail.isEmpty() && country == language_ISO_639_1)
                    xt9CountryOrDetail = country;

                if (xt9CountryOrDetail == country ||
                        ((script == QLocale::SimplifiedHanScript && charsetClassifier == QLatin1String("sb")) ||
                         (script == QLocale::TraditionalHanScript && charsetClassifier == QLatin1String("tb"))))
                    ++score;

                if (locale.territory() == QLocale::Taiwan && xt9CountryOrDetail == QLatin1String("ps_Big5_bpmf_pinyin_CJ"))
                    ++score;
                else if (locale.territory() == QLocale::HongKong && xt9CountryOrDetail == QLatin1String("ps_Big5HKSCS_bpmf_pinyin_CJ"))
                    ++score;

                if (!almClassifier.isEmpty())
                    ++score;

                matchedDictionaries.insert(fileEntry, score);
            }
        }
    }

    if (matchedDictionaries.isEmpty())
        return QString();

    QList<int> scoreList = matchedDictionaries.values();
    std::sort(scoreList.begin(), scoreList.end());
    const int highScore = scoreList.last();
    const QString bestMatch = matchedDictionaries.key(highScore);

    return bestMatch;
}

} // namespace QtVirtualKeyboard
QT_END_NAMESPACE
