// Copyright (C) 2021 The Qt Company Ltd.
// SPDX-License-Identifier: LicenseRef-Qt-Commercial OR GPL-3.0-only

#include "t9writeinputmethod_p.h"
#include <QtVirtualKeyboard/qvirtualkeyboardinputengine.h>
#include <QtVirtualKeyboard/qvirtualkeyboardinputcontext.h>
#include <QtVirtualKeyboard/qvirtualkeyboardtrace.h>
#include "t9writeworker_p.h"
#include <QLoggingCategory>
#include <QDirIterator>
#include <QCryptographicHash>
#include <QTime>
#include <QMetaEnum>
#include <QtCore/QLibraryInfo>
#include <QtVirtualKeyboard/private/settings_p.h>
#include <QtVirtualKeyboard/private/handwritinggesturerecognizer_p.h>
#include <QtVirtualKeyboard/private/qvirtualkeyboardabstractinputmethod_p.h>
#ifdef QT_VIRTUALKEYBOARD_RECORD_TRACE_INPUT
#include <QtVirtualKeyboard/private/unipentrace_p.h>
#include <QStandardPaths>
#endif
#include <QtVirtualKeyboard/qvirtualkeyboarddictionary.h>
#include <QtVirtualKeyboard/qvirtualkeyboarddictionarymanager.h>

#include "decumaStatus.h"
#include "decumaSymbolCategories.h"
#include "decumaLanguages.h"
#include "xxchOem.h"
#include "xt9ldbmanager.h"
#include "t9writewordcandidate_p.h"
#ifdef HAVE_XT9
#include <xt9awime.h>
#include <xt9cpime.h>
#include <xt9jime.h>
#include <xt9kime.h>
#include <xt9callbacks.h>
#include <xt9languagemap.h>
#endif

/*  Set to 1 to enable T9 Write log.

    The log is routed to qDebug() and it can be enabled for troubleshooting
    and when reporting issues. The log must not to be enabled in production
    build.
*/
#define QT_VIRTUALKEYBOARD_CERENCE_HWR_LOG 0

#define CERENCE_HWR_DLM_MAX_WORDS 10000

QT_BEGIN_NAMESPACE
namespace QtVirtualKeyboard {

Q_LOGGING_CATEGORY(lcT9Write, "qt.virtualkeyboard.cerence-hwr")

class T9WriteCaseFormatter
{
public:
    T9WriteCaseFormatter() :
        preferLowercase(false)
    {
    }

    void clear()
    {
        textCaseList.clear();
    }

    void ensureLength(int length, QVirtualKeyboardInputEngine::TextCase textCase)
    {
        if (length <= 0) {
            textCaseList.clear();
            return;
        }
        while (length < textCaseList.size())
            textCaseList.removeLast();
        while (length > textCaseList.size())
            textCaseList.append(textCase);
    }

    QString formatString(const QString &str) const
    {
        QString result;
        QVirtualKeyboardInputEngine::TextCase textCase = QVirtualKeyboardInputEngine::TextCase::Lower;
        for (int i = 0; i < str.length(); ++i) {
            if (i < textCaseList.size())
                textCase = textCaseList.at(i);
            result.append(textCase == QVirtualKeyboardInputEngine::TextCase::Upper ? str.at(i).toUpper() : (preferLowercase ? str.at(i).toLower() : str.at(i)));
        }
        return result;
    }

    bool preferLowercase;

private:
    QList<QVirtualKeyboardInputEngine::TextCase> textCaseList;
};

class T9WriteInputMethodPrivate : public QVirtualKeyboardAbstractInputMethodPrivate
#ifdef HAVE_XT9
        , public Xt9RequestCallback
#endif
{
public:
    Q_DECLARE_PUBLIC(T9WriteInputMethod)

    T9WriteInputMethodPrivate(T9WriteInputMethod *q_ptr) :
        QVirtualKeyboardAbstractInputMethodPrivate(),
        q_ptr(q_ptr),
        cjk(false),
        engineMode(T9WriteInputMethod::EngineMode::Uninitialized),
        traceListHardLimit(32),
        attachedDictionary(nullptr),
        ldbManager(new Xt9LdbManager()),
        resultId(0),
        lastResultId(0),
        resultTimer(0),
        decumaSession(nullptr),
        activeWordIndex(-1),
        arcAdditionStarted(false),
        ignoreUpdate(false),
        textCase(QVirtualKeyboardInputEngine::TextCase::Lower)
#ifdef QT_VIRTUALKEYBOARD_RECORD_TRACE_INPUT
        , unipenTrace()
#endif
    {
#ifdef HAVE_CERENCE_HWR_RESOURCE
        Q_INIT_RESOURCE(qmake_cerencecommondata_db);
        Q_INIT_RESOURCE(qmake_cerencehwrdata_db);
#endif
        const QString pathListSep(
#if defined(Q_OS_WIN32)
            QStringLiteral(";")
#else
            QStringLiteral(":")
#endif
        );
        const QString userHwrDbPath(qEnvironmentVariable("QT_VIRTUALKEYBOARD_CERENCE_HWR_DB_PATH"));
        defaultHwrDbPaths = userHwrDbPath.split(pathListSep, Qt::SkipEmptyParts)
                << QDir(QStringLiteral("%1/qtvirtualkeyboard/cerence/handwriting/").arg(QLibraryInfo::path(QLibraryInfo::DataPath))).absolutePath()
                << QStringLiteral(":/qt-project.org/imports/QtQuick/VirtualKeyboard/Cerence/Handwriting/");
        ldbManager->setPhdEnabled(true);
        for (const QString &searchPath : defaultHwrDbPaths) {
            ldbManager->addSearchPath(searchPath);
        }
    }

    static void *decumaMalloc(size_t size, void *pPrivate)
    {
        Q_UNUSED(pPrivate);
        return malloc(size);
    }

    static void *decumaCalloc(size_t elements, size_t size, void *pPrivate)
    {
        Q_UNUSED(pPrivate);
        return calloc(elements, size);
    }

    static void decumaFree(void *ptr, void *pPrivate)
    {
        Q_UNUSED(pPrivate);
        free(ptr);
    }

#if QT_VIRTUALKEYBOARD_CERENCE_HWR_LOG
    static void decumaLogString(void *pUserData, const char *pLogString, DECUMA_UINT32 nLogStringLength)
    {
        static QMutex s_logMutex;
        static QByteArray s_logString;
        Q_UNUSED(pUserData);
        QMutexLocker guard(&s_logMutex);
        s_logString.append(pLogString, nLogStringLength);
        if (s_logString.endsWith('\n')) {
            while (s_logString.endsWith('\n'))
                s_logString.chop(1);
            qDebug() << (const char *)s_logString.constData();
            s_logString.clear();
        }
    }
#endif

    static const char *engineModeToString(T9WriteInputMethod::EngineMode mode)
    {
        return QMetaEnum::fromType<T9WriteInputMethod::EngineMode>().key(static_cast<int>(mode));
    }

    bool initEngine(T9WriteInputMethod::EngineMode newEngineMode)
    {
        if (engineMode == newEngineMode)
            return engineMode != T9WriteInputMethod::EngineMode::Uninitialized;

        qCDebug(lcT9Write) << "T9WriteInputMethodPrivate::initEngine()" << engineModeToString(newEngineMode);

        if (decumaSession)
            exitEngine();

        if (newEngineMode == T9WriteInputMethod::EngineMode::Uninitialized)
            return false;

        switch (newEngineMode) {
        case T9WriteInputMethod::EngineMode::Alphabetic:
        case T9WriteInputMethod::EngineMode::Arabic:
        case T9WriteInputMethod::EngineMode::Hebrew:
        case T9WriteInputMethod::EngineMode::Thai:
            cjk = false;
            break;
        case T9WriteInputMethod::EngineMode::SimplifiedChinese:
        case T9WriteInputMethod::EngineMode::TraditionalChinese:
        case T9WriteInputMethod::EngineMode::HongKongChinese:
        case T9WriteInputMethod::EngineMode::Japanese:
        case T9WriteInputMethod::EngineMode::Korean:
            cjk = true;
            break;
        default:
            Q_ASSERT(0 && "Invalid T9WriteInputMethod::EngineMode!");
            return false;
        }
        engineMode = newEngineMode;

        memset(&sessionSettings, 0, sizeof(sessionSettings));

        QString hwrDb = findHwrDb(engineMode);
        hwrDbFile.setFileName(hwrDb);
        if (!hwrDbFile.open(QIODevice::ReadOnly)) {
            qCCritical(lcT9Write) << "Could not open HWR database" << hwrDb;
            exitEngine();
            return false;
        }

        sessionSettings.pStaticDB = reinterpret_cast<DECUMA_STATIC_DB_PTR>(hwrDbFile.map(0, hwrDbFile.size(), QFile::NoOptions));
        if (!sessionSettings.pStaticDB) {
            qCCritical(lcT9Write) << "Could not read HWR database" << hwrDb;
            exitEngine();
            return false;
        }

        symbolCategories.append(DECUMA_CATEGORY_ANSI);
        languageCategories.append(DECUMA_LANG_EN);

        sessionSettings.recognitionMode = mcrMode;
        sessionSettings.writingDirection = unknownWriting;
        sessionSettings.charSet.pSymbolCategories = symbolCategories.data();
        sessionSettings.charSet.nSymbolCategories = static_cast<DECUMA_UINT8>(symbolCategories.size());
        sessionSettings.charSet.pLanguages = languageCategories.data();
        sessionSettings.charSet.nLanguages = static_cast<DECUMA_UINT8>(languageCategories.size());

        session = QByteArray(static_cast<int>(DECUMA_API(GetSessionSize)()), 0);
        decumaSession = reinterpret_cast<DECUMA_SESSION *>(!session.isEmpty() ? session.data() : nullptr);

        DECUMA_STATUS status = DECUMA_API(BeginSession)(decumaSession, &sessionSettings, &memFuncs);
        Q_ASSERT(status == decumaNoError);
        if (status != decumaNoError) {
            qCCritical(lcT9Write) << "Could not initialize engine" << status;
            exitEngine();
            return false;
        }

#if QT_VIRTUALKEYBOARD_CERENCE_HWR_LOG
        DECUMA_API(StartLogging)(decumaSession, 0, decumaLogString);
#endif

        worker.reset(new T9WriteWorker(decumaSession, cjk));
        worker->start();

        Q_Q(T9WriteInputMethod);
        resultListChangedConnection = QObjectPrivate::connect(
                    q, &T9WriteInputMethod::resultListChanged,
                    this, &T9WriteInputMethodPrivate::processResultCheckTimer,
                    Qt::QueuedConnection);
        availableDictionariesChangedConnection = QObjectPrivate::connect(QVirtualKeyboardDictionaryManager::instance(),
                   &QVirtualKeyboardDictionaryManager::availableDictionariesChanged,
                   this, &T9WriteInputMethodPrivate::onAvailableDynamicDictionariesChanged);
        activeDictionariesChangedConnection = QObjectPrivate::connect(QVirtualKeyboardDictionaryManager::instance(),
                   &QVirtualKeyboardDictionaryManager::activeDictionariesChanged,
                   this, &T9WriteInputMethodPrivate::onActiveDynamicDictionariesChanged);

#ifdef HAVE_XT9
        bindSettings();
#endif

        return true;
    }

    void exitEngine()
    {
        qCDebug(lcT9Write) << "T9WriteInputMethodPrivate::exitEngine()";

#ifdef HAVE_XT9
        unbindSettings();
#endif

        QObject::disconnect(resultListChangedConnection);
        QObject::disconnect(availableDictionariesChangedConnection);
        QObject::disconnect(activeDictionariesChangedConnection);

        worker.reset();

#ifdef HAVE_XT9
        xt9Exit();
#endif

        if (sessionSettings.pStaticDB) {
            hwrDbFile.unmap(const_cast<uchar *>(reinterpret_cast<const uchar *>(sessionSettings.pStaticDB)));
            hwrDbFile.close();
        }

        dlmDeactivate();

        if (attachedDictionary) {
            detachDictionary(attachedDictionary);
            attachedDictionary.reset();
        }
        loadedDictionary.reset();

        for (auto &dynamicDictionary : attachedDynamicDictionaries) {
            detachDictionary(dynamicDictionary);
        }
        attachedDynamicDictionaries.clear();
        dynamicDictionaries.clear();

        if (decumaSession) {
#if QT_VIRTUALKEYBOARD_CERENCE_HWR_LOG
            DECUMA_API(StopLogging)(decumaSession);
#endif
            DECUMA_API(EndSession)(decumaSession);
            decumaSession = nullptr;
            session.clear();
        }

        memset(&sessionSettings, 0, sizeof(sessionSettings));

        symbolCategories.clear();
        languageCategories.clear();

        ldbManager->closeAll();

        engineMode = T9WriteInputMethod::EngineMode::Uninitialized;
        cjk = false;
    }

#ifdef HAVE_XT9
    void xt9Init(const QLocale &locale, QVirtualKeyboardInputEngine::InputMode inputMode, T9WriteInputMethod::EngineMode newEngineMode)
    {
        ET9U32 dwFirstLdbNum = Xt9LanguageMap::languageId(locale);
        ET9U32 eInputMode = ET9AWInputMode_Default;

        xt9DetachAllDynamicDictionaries();

        switch (newEngineMode) {
        case T9WriteInputMethod::EngineMode::SimplifiedChinese:
        case T9WriteInputMethod::EngineMode::TraditionalChinese:
        case T9WriteInputMethod::EngineMode::HongKongChinese:
            if (inputMode == QVirtualKeyboardInputEngine::InputMode::ChineseHandwriting) {
                xt9Ime.reset(new Xt9CpIme(this));
                switch (locale.script()) {
                case QLocale::SimplifiedHanScript:
                    if (static_cast<Xt9CpIme *>(xt9Ime.data())) {
                        eInputMode = ET9CPMODE_PINYIN;
                    }
                    break;
                default:
                    break;
                }
            } else {
                if (xt9IsAlphabeticCoreDisabled()) {
                    xt9Exit();
                    return;
                }
                xt9Ime.reset(new Xt9AwIme(this));
                dwFirstLdbNum = ET9LIDEnglish_UK;
            }
            break;

        case T9WriteInputMethod::EngineMode::Japanese:
            xt9Ime.reset(new Xt9JIme(this));
            eInputMode = ET9AWInputMode_RomajiConversion;
            break;

        case T9WriteInputMethod::EngineMode::Korean:
            xt9Ime.reset(new Xt9KIme(this));
            break;

        default:
            if (xt9IsAlphabeticCoreDisabled()) {
                xt9Exit();
                return;
            }
            xt9Ime.reset(new Xt9AwIme(this));
            break;
        }

        xt9Ime->ldbManager = ldbManager;
        xt9Ime->sysInit();
        xt9Ime->setWorkingDirectory(Settings::instance()->userDataPath());
        if (xt9DynamicDictionaries.isEmpty())
            xt9Ime->removeAllIndexes();

        // PHD must be disabled during XT9 init to prevent finding
        // T9 Write specific dictionary files.
        ldbManager->setPhdEnabled(false);

        xt9Ime->ldbInit(dwFirstLdbNum, ET9PLIDNone, eInputMode);

        ldbManager->setPhdEnabled(true);

        onDefaultDictionaryDisabledChanged();
        onAvailableDynamicDictionariesChanged();
        onActiveDynamicDictionariesChanged();
    }

    void xt9Exit()
    {
        if (xt9Ime)
            xt9Ime->removeAllIndexes();

        Q_Q(T9WriteInputMethod);
        QVirtualKeyboardDictionaryManager *dictionaryManager = QVirtualKeyboardDictionaryManager::instance();
        const QStringList availableDictionaries = dictionaryManager->availableDictionaries();
        for (const QString &dictionaryName : availableDictionaries) {
            QVirtualKeyboardDictionary *dictionary = dictionaryManager->dictionary(dictionaryName);
            dictionary->disconnect(q);  // lambdas
        }

        xt9AttachedDynamicDictionaries.clear();
        xt9DynamicDictionaries.clear();
        xt9DynamicDictionaryNextId = 0;

        xt9Ime.reset();
    }

    void bindSettings()
    {
        if (!defaultInputMethodDisabledChangedConnection)
            defaultInputMethodDisabledChangedConnection = QObjectPrivate::connect(
                        Settings::instance(), &Settings::defaultInputMethodDisabledChanged,
                        this, &T9WriteInputMethodPrivate::onXt9AlphabeticCoreDisabledChanged);
        if (!defaultDictionaryDisabledChangedConnection)
            defaultDictionaryDisabledChangedConnection = QObjectPrivate::connect(
                        Settings::instance(), &Settings::defaultDictionaryDisabledChanged,
                        this, &T9WriteInputMethodPrivate::onDefaultDictionaryDisabledChanged);
        if (!userDataResetConnection)
            userDataResetConnection = QObjectPrivate::connect(
                        Settings::instance(), &Settings::userDataReset,
                        this, &T9WriteInputMethodPrivate::onUserDataReset);
    }

    void unbindSettings()
    {
        QObject::disconnect(defaultInputMethodDisabledChangedConnection);
        QObject::disconnect(defaultDictionaryDisabledChangedConnection);
        QObject::disconnect(userDataResetConnection);
    }

    void onXt9AlphabeticCoreDisabledChanged()
    {
        if (xt9IsAlphabeticCoreDisabled()) {
            xt9Exit();
        } else if (!xt9Ime) {
            Q_Q(T9WriteInputMethod);
            const QVirtualKeyboardInputEngine::InputMode inputMode = q->inputEngine()->inputMode();
            const QLocale locale = QLocale(q->inputContext()->locale());
            const DECUMA_UINT32 language = mapToDecumaLanguage(locale, inputMode);
            const T9WriteInputMethod::EngineMode newEngineMode = mapLocaleToEngineMode(locale, language);
            xt9Init(locale, inputMode, newEngineMode);
        }
    }

    static bool xt9IsAlphabeticCoreDisabled()
    {
        Settings *settings = Settings::instance();
        return settings->isDefaultInputMethodDisabled();
    }

    void onDefaultDictionaryDisabledChanged()
    {
        if (Xt9AwIme *xt9AwIme = dynamic_cast<Xt9AwIme *>(xt9Ime.data()))
            xt9AwIme->setLdbEnabled(!Settings::instance()->isDefaultDictionaryDisabled());
    }

    void onUserDataReset()
    {
        dlmDeactivate();
#ifdef HAVE_XT9
        xt9Exit();
#endif
    }

    ET9STATUS request(ET9_Request *const pRequest) override
    {
        Q_Q(T9WriteInputMethod);

        switch (pRequest->eType) {
        case ET9_REQ_BufferContext:
        {
            QVirtualKeyboardInputContext *ic = q->inputContext();
            if (!ic)
                break;

            const ET9U32 dwContextLen = static_cast<ET9U32>(ic->cursorPosition());
            const ET9U32 dwStartIndex =
                    dwContextLen <= pRequest->data.sBufferContextInfo.dwMaxBufLen ?
                        0 : dwContextLen - pRequest->data.sBufferContextInfo.dwMaxBufLen;

            pRequest->data.sBufferContextInfo.dwBufLen = dwContextLen - dwStartIndex;
            const QString surroundingText = ic->surroundingText();

            memcpy(pRequest->data.sBufferContextInfo.psBuf, surroundingText.utf16() + dwStartIndex,
                   pRequest->data.sBufferContextInfo.dwBufLen * sizeof(ET9SYMB));

            break;
        }

        default:
            break;
        }

        return ET9STATUS_NONE;
    }

    bool xt9AllSymbsArePinyin(const QString &symbs) const
    {
        bool allSymbsArePinyin = false;
        for (const QChar &symb : symbs) {
            const ushort ucs = symb.unicode();
            allSymbsArePinyin = ET9CPIsPinyinSymbol(ucs);
            if (!allSymbsArePinyin)
                break;
        }
        return allSymbsArePinyin;
    }

    bool xt9AttachDictionary(const QString &dictionaryName)
    {
        if (!xt9DynamicDictionaries.contains(dictionaryName))
            return false;

        const quint16 id = xt9DynamicDictionaries.value(dictionaryName);
        qCDebug(lcT9Write) << "T9WriteInputMethodPrivate::xt9AttachDictionary():" << dictionaryName << id;
        xt9Ime->mountIndex(id);
        xt9AttachedDynamicDictionaries[dictionaryName] = id;

        return true;
    }

    void xt9DetachDictionary(const QString &dictionaryName)
    {
        if (!xt9AttachedDynamicDictionaries.contains(dictionaryName))
            return;

        const quint16 id = xt9AttachedDynamicDictionaries[dictionaryName];
        qCDebug(lcT9Write) << "T9WriteInputMethodPrivate::xt9DetachDictionary():" << dictionaryName << id;
        xt9Ime->unmountIndex(id);
        xt9AttachedDynamicDictionaries.remove(dictionaryName);
    }
#endif

#ifdef HAVE_XT9
    void xt9DetachAllDynamicDictionaries()
    {
        if (xt9Ime) {
            const QStringList dictionaryNames = xt9AttachedDynamicDictionaries.keys();
            for (const QString &dictionaryName : dictionaryNames) {
                xt9DetachDictionary(dictionaryName);
            }
        }
        xt9AttachedDynamicDictionaries.clear();
    }
#endif

    QStringList xt9BuildSelectionList(const QString &exactWord, int *defaultListIndex)
    {
#ifdef HAVE_XT9
        if (!xt9Ime)
            return QStringList();

        xt9Ime->cursorMoved();

        Q_Q(T9WriteInputMethod);
        bool forceLowerCase =
                engineMode == T9WriteInputMethod::EngineMode::SimplifiedChinese &&
                q->inputEngine()->inputMode() == QVirtualKeyboardInputEngine::InputMode::ChineseHandwriting &&
                xt9AllSymbsArePinyin(exactWord);

        ET9ClearAllSymbs(&xt9Ime->sWordSymbInfo);
        for (const QChar &c : exactWord) {
            ET9AddExplicitSymb(&xt9Ime->sWordSymbInfo, c.unicode(), 0, !forceLowerCase && c.isUpper() ? ET9SHIFT : ET9NOSHIFT, ET9_NO_ACTIVE_INDEX);
        }

        ET9SYMB gestureValue = 0;
        return xt9Ime->buildSelectionList(defaultListIndex, &gestureValue);
#else
        return QStringList();
#endif
    }

    void appendWordCandidates(QList<T9WriteWordCandidate> &aWordCandidates, int &activeWordIndex, const QString &exactWord, const QStringList &wordCandidatesToAppend, int defaultListIndex, T9WriteWordCandidate::Origin origin) const
    {
        for (int index = 0; index < wordCandidatesToAppend.size(); ++index) {
            const T9WriteWordCandidate wordCandidate(wordCandidatesToAppend[index], index, origin);
            if (!aWordCandidates.contains(wordCandidate)) {
                bool isDefaultIndex = defaultListIndex > 0 &&
                        index == defaultListIndex && !cjk &&
                        origin == T9WriteWordCandidate::Origin::XT9;
                if (isDefaultIndex) {
                    activeWordIndex = qMin(aWordCandidates.size(), 1);
                    aWordCandidates.insert(activeWordIndex, wordCandidate);
                } else {
                    aWordCandidates.append(wordCandidate);
                }
            }
        }

        if (aWordCandidates.isEmpty()) {
            aWordCandidates.append(T9WriteWordCandidate(exactWord));
        }
    }

    QString findHwrDb(T9WriteInputMethod::EngineMode mode) const
    {
        for (const QString &defaultHwrDbPath : defaultHwrDbPaths) {
            const QString result = findHwrDb(mode, defaultHwrDbPath);
            if (!result.isEmpty())
                return result;
        }

        qCCritical(lcT9Write) << "Could not find HWR database for" << engineModeToString(mode);
        return QString();
    }

    QString findHwrDb(T9WriteInputMethod::EngineMode mode, const QString &dir) const
    {
        QString hwrDbPath(QDir::fromNativeSeparators(dir));
        if (!hwrDbPath.endsWith(QLatin1Char('/')))
            hwrDbPath.append(QLatin1Char('/'));
        switch (mode) {
        case T9WriteInputMethod::EngineMode::Alphabetic:
            hwrDbPath.append(QLatin1String("hwrDB_le.bin"));
            break;
        case T9WriteInputMethod::EngineMode::Arabic:
            hwrDbPath.append(QLatin1String("arabic/hwrDB_le.bin"));
            break;
        case T9WriteInputMethod::EngineMode::Hebrew:
            hwrDbPath.append(QLatin1String("hebrew/hwrDB_le.bin"));
            break;
        case T9WriteInputMethod::EngineMode::Thai:
            hwrDbPath.append(QLatin1String("thai/hwrDB_le.bin"));
            break;
        case T9WriteInputMethod::EngineMode::SimplifiedChinese:
            hwrDbPath.append(QLatin1String("cjk_S_gb18030_le.hdb"));
            break;
        case T9WriteInputMethod::EngineMode::TraditionalChinese:
        case T9WriteInputMethod::EngineMode::HongKongChinese:
            hwrDbPath.append(QLatin1String("cjk_HK_std_le.hdb"));
            break;
        case T9WriteInputMethod::EngineMode::Japanese:
            hwrDbPath.append(QLatin1String("cjk_J_std_le.hdb"));
            break;
        case T9WriteInputMethod::EngineMode::Korean:
            hwrDbPath.append(QLatin1String("cjk_K_mkt_le.hdb"));
            break;
        default:
            return QString();
        }
        if (!QFileInfo::exists(hwrDbPath)) {
            return QString();
        }
        return hwrDbPath;
    }

    QString findDictionary(const QLocale &locale, DECUMA_SRC_DICTIONARY_TYPE &srcType)
    {
        srcType = numberOfSrcDictionaryTypes;

        QString dictionary = ldbManager->findDictionary(locale);
        if (!dictionary.isEmpty()) {
            if (dictionary.endsWith(QLatin1String(".ldb"))) {
                srcType = decumaPortableHWRDictionary;
            } else if (dictionary.endsWith(QLatin1String(".phd"))) {
                srcType = decumaPortableHWRDictionary;
            } else {
                qCCritical(lcT9Write) << "Incompatible dictionary" << dictionary;
                dictionary.clear();
            }
        }

        return dictionary;
    }

    bool attachDictionary(const QSharedPointer<T9WriteAbstractDictionary> &dictionary)
    {
        const std::lock_guard<QRecursiveMutex> dictionaryGuard(dictionaryLock);
        Q_ASSERT(decumaSession != nullptr);
        Q_ASSERT(dictionary != nullptr);
        qCDebug(lcT9Write) << "T9WriteInputMethodPrivate::attachDictionary():" << dictionary->name();
        DECUMA_STATUS status = DECUMA_API(AttachDictionary)(decumaSession, dictionary->data(), static_cast<DECUMA_UINT32>(dictionary->size()));
        return status == decumaNoError;
    }

    void detachDictionary(const QSharedPointer<T9WriteAbstractDictionary> &dictionary)
    {
        const std::lock_guard<QRecursiveMutex> dictionaryGuard(dictionaryLock);
        if (!dictionary)
            return;

        qCDebug(lcT9Write) << "T9WriteInputMethodPrivate::detachDictionary():" << dictionary->name();

        Q_ASSERT(decumaSession != nullptr);
        DECUMA_STATUS status = DECUMA_API(DetachDictionary)(decumaSession, dictionary->data());
        Q_UNUSED(status);
        Q_ASSERT(status == decumaNoError);
    }

    bool setInputMode(const QLocale &locale, QVirtualKeyboardInputEngine::InputMode inputMode)
    {
        Q_Q(T9WriteInputMethod);
        qCDebug(lcT9Write) << "T9WriteInputMethodPrivate::setInputMode():" << locale << inputMode;

        finishRecognition();

        // All tasks must be completed before changing the session settings
        if (worker) {
            worker->waitForAllTasks();
            dictionaryTask.reset();
        }

        DECUMA_UINT32 language = mapToDecumaLanguage(locale, inputMode);
        if (language == DECUMA_LANG_GSMDEFAULT) {
            qCCritical(lcT9Write) << "Language is not supported" << locale.name();
            return false;
        }

        T9WriteInputMethod::EngineMode newEngineMode = mapLocaleToEngineMode(locale, language);

#ifdef HAVE_XT9
        xt9Init(locale, inputMode, newEngineMode);
#endif

        if (!initEngine(newEngineMode)) {
#ifdef HAVE_XT9
            xt9Exit();
#endif
            return false;
        }

        onAvailableDynamicDictionariesChanged();
        onActiveDynamicDictionariesChanged();

        const Qt::InputMethodHints inputMethodHints = q->inputContext()->inputMethodHints();
        if (!inputMethodHints.testFlag(Qt::ImhHiddenText) && !inputMethodHints.testFlag(Qt::ImhNoPredictiveText) &&
                !inputMethodHints.testFlag(Qt::ImhSensitiveData)) {
            dlmActivate();
        }

        int isLanguageSupported = 0;
        DECUMA_API(DatabaseIsLanguageSupported)(sessionSettings.pStaticDB, language, &isLanguageSupported);
        if (!isLanguageSupported) {
            qCCritical(lcT9Write) << "Language is not supported" << locale.name();
            return false;
        }

        bool languageChanged = languageCategories.isEmpty() || languageCategories.first() != language;
        languageCategories.clear();
        languageCategories.append(language);

        // Add English as secondary language for non-latin languages.
        // T9 Write requires it for punctuation and latin symbols if
        // included in the symbol categories.
        if (locale.script() != QLocale::LatinScript)
            languageCategories.append(DECUMA_LANG_EN);

        if (!updateSymbolCategories(language, locale, inputMode))
            return false;
        updateRecognitionMode(language, locale, inputMode);
        static const QList<DECUMA_UINT32> rtlLanguages = QList<DECUMA_UINT32>()
                << DECUMA_LANG_AR << DECUMA_LANG_IW << DECUMA_LANG_FA << DECUMA_LANG_UR;
        sessionSettings.writingDirection = rtlLanguages.contains(language) ? rightToLeft : leftToRight;

        // Enable multi-threaded recognition if available.
#ifdef DECUMA_USE_MULTI_THREAD
        // Note: This feature requires T9 Write v8.0.0 or later,
        //       and feature enabled in the SDK.
#if CERENCEHANDWRITINGAPIMAJORVERNUM > 28
        sessionSettings.bUseThreads = 1;
#else
        sessionSettings.nMaxThreads = qMax(QThread::idealThreadCount(), 0);
#endif
#endif

        qCDebug(lcT9Write) << " -> language categories:" << languageCategories;
        qCDebug(lcT9Write) << " -> symbol categories:" << symbolCategories;
        qCDebug(lcT9Write) << " -> recognition mode:" << sessionSettings.recognitionMode;

        // Change session settings
        sessionSettings.charSet.pSymbolCategories = symbolCategories.data();
        sessionSettings.charSet.nSymbolCategories = static_cast<DECUMA_UINT8>(symbolCategories.size());
        sessionSettings.charSet.pLanguages = languageCategories.data();
        sessionSettings.charSet.nLanguages = static_cast<DECUMA_UINT8>(languageCategories.size());
        DECUMA_STATUS status = DECUMA_API(ChangeSessionSettings)(decumaSession, &sessionSettings);

        if (status == decumaUnsupportedLanguageInUcrMode || status == decumaUnsupportedSymbolCategoryInUcrMode) {
            sessionSettings.recognitionMode = mcrMode;
            status = DECUMA_API(ChangeSessionSettings)(decumaSession, &sessionSettings);
        }

        if (status != decumaNoError)
            qCWarning(lcT9Write) << "Failed to configure HWR engine" << status;

        caseFormatter.preferLowercase = q->inputContext()->inputMethodHints().testFlag(Qt::ImhPreferLowercase);

        updateDictionary(language, locale, languageChanged);

        return status == decumaNoError;
    }

    T9WriteInputMethod::EngineMode mapLocaleToEngineMode(const QLocale &locale, DECUMA_UINT32 language = 0)
    {
#ifdef HAVE_CERENCE_HWR_CJK
        switch (locale.language()) {
        case QLocale::Chinese: {
            if (locale.script() == QLocale::TraditionalChineseScript)
                return locale.territory() == QLocale::HongKong ? T9WriteInputMethod::EngineMode::HongKongChinese : T9WriteInputMethod::EngineMode::TraditionalChinese;
            return T9WriteInputMethod::EngineMode::SimplifiedChinese;
        }
        case QLocale::Japanese:
            return T9WriteInputMethod::EngineMode::Japanese;
        case QLocale::Korean:
            return T9WriteInputMethod::EngineMode::Korean;
        default:
            break;
        }
#else
        Q_UNUSED(locale);
        Q_UNUSED(language);
#endif

#ifdef HAVE_CERENCE_HWR_ALPHABETIC
        switch (locale.script()) {
        case QLocale::ArabicScript:
            return T9WriteInputMethod::EngineMode::Arabic;
        case QLocale::HebrewScript:
            return T9WriteInputMethod::EngineMode::Hebrew;
        case QLocale::ThaiScript:
            return language == DECUMA_LANG_EN ? T9WriteInputMethod::EngineMode::Alphabetic
                                              : T9WriteInputMethod::EngineMode::Thai;
        default:
            return T9WriteInputMethod::EngineMode::Alphabetic;
        }
#else
        return T9WriteInputMethod::EngineMode::Uninitialized;
#endif
    }

    DECUMA_UINT32 mapToDecumaLanguage(const QLocale &locale, QVirtualKeyboardInputEngine::InputMode inputMode)
    {
        struct LanguageMap {
            QLocale::Language localeLanguage;
            DECUMA_UINT16 decumaLanguage;
        };
        static const LanguageMap languageMap[] = {
            { QLocale::Language::Afrikaans,          DECUMA_LANG_AF },
            { QLocale::Language::Albanian,           DECUMA_LANG_SQ },
            { QLocale::Language::Arabic,             DECUMA_LANG_AR },
            { QLocale::Language::Azerbaijani,        DECUMA_LANG_AZ },
            { QLocale::Language::Basque,             DECUMA_LANG_EU },
            { QLocale::Language::Belarusian,         DECUMA_LANG_BE },
            { QLocale::Language::Bengali,            DECUMA_LANG_BN },
            { QLocale::Language::Bulgarian,          DECUMA_LANG_BG },
            { QLocale::Language::Catalan,            DECUMA_LANG_CA },
            { QLocale::Language::Chinese,            DECUMA_LANG_PRC },
            { QLocale::Language::Croatian,           DECUMA_LANG_HR },
            { QLocale::Language::Czech,              DECUMA_LANG_CS },
            { QLocale::Language::Danish,             DECUMA_LANG_DA },
            { QLocale::Language::Dutch,              DECUMA_LANG_NL },
            { QLocale::Language::English,            DECUMA_LANG_EN },
            { QLocale::Language::Estonian,           DECUMA_LANG_ET },
            { QLocale::Language::Finnish,            DECUMA_LANG_FI },
            { QLocale::Language::French,             DECUMA_LANG_FR },
            { QLocale::Language::Galician,           DECUMA_LANG_GL },
            { QLocale::Language::German,             DECUMA_LANG_DE },
            { QLocale::Language::Greek,              DECUMA_LANG_EL },
            { QLocale::Language::Gujarati,           DECUMA_LANG_GU },
            { QLocale::Language::Hausa,              DECUMA_LANG_HA },
            { QLocale::Language::Hebrew,             DECUMA_LANG_IW },
            { QLocale::Language::Hindi,              DECUMA_LANG_HI },
            { QLocale::Language::Hungarian,          DECUMA_LANG_HU },
            { QLocale::Language::Icelandic,          DECUMA_LANG_IS },
            { QLocale::Language::Indonesian,         DECUMA_LANG_IN },
            { QLocale::Language::Italian,            DECUMA_LANG_IT },
            { QLocale::Language::Japanese,           DECUMA_LANG_JP },
            { QLocale::Language::Kannada,            DECUMA_LANG_KN },
            { QLocale::Language::Kazakh,             DECUMA_LANG_KK },
            { QLocale::Language::Khmer,              DECUMA_LANG_KM },
            { QLocale::Language::Kirghiz,            DECUMA_LANG_KY },
            { QLocale::Language::Korean,             DECUMA_LANG_KO },
            { QLocale::Language::Latvian,            DECUMA_LANG_LV },
            { QLocale::Language::Lithuanian,         DECUMA_LANG_LT },
            { QLocale::Language::Macedonian,         DECUMA_LANG_MK },
            { QLocale::Language::Malay,              DECUMA_LANG_MS },
            { QLocale::Language::Malayalam,          DECUMA_LANG_ML },
            { QLocale::Language::Marathi,            DECUMA_LANG_MR },
            { QLocale::Language::Mongolian,          DECUMA_LANG_MN },
            { QLocale::Language::NorwegianBokmal,    DECUMA_LANG_NO },
            { QLocale::Language::Persian,            DECUMA_LANG_FA },
            { QLocale::Language::Polish,             DECUMA_LANG_PL },
            { QLocale::Language::Portuguese,         DECUMA_LANG_PT },
            { QLocale::Language::Punjabi,            DECUMA_LANG_PA },
            { QLocale::Language::Romanian,           DECUMA_LANG_RO },
            { QLocale::Language::Russian,            DECUMA_LANG_RU },
            { QLocale::Language::Serbian,            DECUMA_LANG_SRCY },
            { QLocale::Language::Sinhala,            DECUMA_LANG_SI },
            { QLocale::Language::Slovak,             DECUMA_LANG_SK },
            { QLocale::Language::Slovenian,          DECUMA_LANG_SL },
            { QLocale::Language::SouthernSotho,      DECUMA_LANG_ST },
            { QLocale::Language::Spanish,            DECUMA_LANG_ES },
            { QLocale::Language::Swahili,            DECUMA_LANG_SW },
            { QLocale::Language::Swedish,            DECUMA_LANG_SV },
            { QLocale::Language::Tajik,              DECUMA_LANG_TG },
            { QLocale::Language::Tamil,              DECUMA_LANG_TA },
            { QLocale::Language::Telugu,             DECUMA_LANG_TE },
            { QLocale::Language::Thai,               DECUMA_LANG_TH },
            { QLocale::Language::Turkish,            DECUMA_LANG_TR },
            { QLocale::Language::Ukrainian,          DECUMA_LANG_UK },
            { QLocale::Language::Urdu,               DECUMA_LANG_UR },
            { QLocale::Language::Uzbek,              DECUMA_LANG_UZ },
            { QLocale::Language::Vietnamese,         DECUMA_LANG_VI },
            // Last entry
            { QLocale::Language::AnyLanguage,        DECUMA_LANG_GSMDEFAULT }
        };

        const int localeLanguage = locale.language();
        const LanguageMap *languageMapIterator = languageMap;
        for (; languageMapIterator->localeLanguage != QLocale::Language::AnyLanguage &&
               languageMapIterator->localeLanguage != localeLanguage; languageMapIterator++) {}

        DECUMA_UINT32 language = languageMapIterator->decumaLanguage;
        if (language == DECUMA_LANG_PRC) {
            if (inputMode != QVirtualKeyboardInputEngine::InputMode::ChineseHandwriting)
                language = DECUMA_LANG_EN;
            else if (locale.script() == QLocale::TraditionalChineseScript)
                language = DECUMA_LANG_HK; // Common language for the traditional script
        } else if (language == DECUMA_LANG_JP) {
            if (inputMode != QVirtualKeyboardInputEngine::InputMode::JapaneseHandwriting)
                language = DECUMA_LANG_EN;
        } else if (language == DECUMA_LANG_KO) {
            if (inputMode != QVirtualKeyboardInputEngine::InputMode::KoreanHandwriting)
                language = DECUMA_LANG_EN;
        } else if (language == DECUMA_LANG_SRCY) {
            if (inputMode != QVirtualKeyboardInputEngine::InputMode::Cyrillic)
                language = DECUMA_LANG_SRLA;
        } else if (language == DECUMA_LANG_AR || language == DECUMA_LANG_FA) {
            if (inputMode != QVirtualKeyboardInputEngine::InputMode::Arabic && inputMode != QVirtualKeyboardInputEngine::InputMode::Numeric)
                language = DECUMA_LANG_EN;
        } else if (language == DECUMA_LANG_IW) {
            if (inputMode != QVirtualKeyboardInputEngine::InputMode::Hebrew)
                language = DECUMA_LANG_EN;
        } else if (language == DECUMA_LANG_TH) {
            if (inputMode != QVirtualKeyboardInputEngine::InputMode::Thai)
                language = DECUMA_LANG_EN;
        }

        return language;
    }

    void updateRecognitionMode(DECUMA_UINT32 language, const QLocale &locale,
                               QVirtualKeyboardInputEngine::InputMode inputMode)
    {
        Q_Q(T9WriteInputMethod);
        Q_UNUSED(language);
        Q_UNUSED(locale);

        // Select recognition mode
        // Note: MCR mode is preferred, as it does not require recognition
        //       timer and provides better user experience.
        sessionSettings.recognitionMode = mcrMode;

        // T9 Write Alphabetic v8.0.0 supports UCR mode for specific languages
        if (!cjk) {
            switch (inputMode) {
            case QVirtualKeyboardInputEngine::InputMode::Latin:
                sessionSettings.recognitionMode = ucrMode;
                break;
            case QVirtualKeyboardInputEngine::InputMode::Arabic:
                sessionSettings.recognitionMode = ucrMode;
                break;
            case QVirtualKeyboardInputEngine::InputMode::Cyrillic:
                sessionSettings.recognitionMode = ucrMode;
                break;
            case QVirtualKeyboardInputEngine::InputMode::Hebrew:
            case QVirtualKeyboardInputEngine::InputMode::Thai:
                sessionSettings.recognitionMode = ucrMode;
                break;
            default:
                break;
            }
        }

        // Use scrMode with hidden text or with no predictive mode
        if (inputMode != QVirtualKeyboardInputEngine::InputMode::ChineseHandwriting &&
                inputMode != QVirtualKeyboardInputEngine::InputMode::JapaneseHandwriting &&
                inputMode != QVirtualKeyboardInputEngine::InputMode::KoreanHandwriting) {
            const Qt::InputMethodHints inputMethodHints = q->inputContext()->inputMethodHints();
            if (inputMethodHints.testFlag(Qt::ImhHiddenText) || inputMethodHints.testFlag(Qt::ImhNoPredictiveText))
                sessionSettings.recognitionMode = scrMode;
        }
    }

    bool updateSymbolCategories(DECUMA_UINT32 language, const QLocale &locale,
                                QVirtualKeyboardInputEngine::InputMode inputMode)
    {
        // Handle CJK in separate method
        if (cjk)
            return updateSymbolCategoriesCjk(language, locale, inputMode);

        symbolCategories.clear();

        // Choose the symbol categories by input mode, script and input method hints
        bool leftToRightGestures = true;
        Q_Q(T9WriteInputMethod);
        const Qt::InputMethodHints inputMethodHints = q->inputContext()->inputMethodHints();
        switch (inputMode) {
        case QVirtualKeyboardInputEngine::InputMode::Latin:
            if (inputMethodHints.testFlag(Qt::ImhEmailCharactersOnly)) {
                symbolCategories.append(DECUMA_CATEGORY_EMAIL);
            } else if (inputMethodHints.testFlag(Qt::ImhUrlCharactersOnly)) {
                symbolCategories.append(DECUMA_CATEGORY_URL);
            } else {
                if (language == DECUMA_LANG_EN || language == DECUMA_LANG_NL ||
                        language == DECUMA_LANG_MS || language == DECUMA_LANG_IN)
                    symbolCategories.append(DECUMA_CATEGORY_ANSI);
                else
                    symbolCategories.append(DECUMA_CATEGORY_ISO8859_1);
                symbolCategories.append(DECUMA_CATEGORY_DIGIT);
                symbolCategories.append(DECUMA_CATEGORY_BASIC_PUNCTUATIONS);
                symbolCategories.append(DECUMA_CATEGORY_CONTRACTION_MARK);
                if (language == DECUMA_LANG_ES)
                    symbolCategories.append(DECUMA_CATEGORY_SPANISH_PUNCTUATIONS);
                else if (language == DECUMA_LANG_VI)
                    symbolCategories.append(DECUMA_CATEGORY_VIETNAMESE_SUPPLEMENTS);
            }
            break;

        case QVirtualKeyboardInputEngine::InputMode::Numeric:
            if (language == DECUMA_LANG_AR || language == DECUMA_LANG_FA) {
                symbolCategories.append(DECUMA_CATEGORY_ARABIC_NUM_MODE);
                symbolCategories.append(DECUMA_CATEGORY_ARABIC_GESTURES);
                leftToRightGestures = false;
                break;
            }
            symbolCategories.append(DECUMA_CATEGORY_DIGIT);
            if (!inputMethodHints.testFlag(Qt::ImhDigitsOnly))
                symbolCategories.append(DECUMA_CATEGORY_NUM_SUP);
            break;

        case QVirtualKeyboardInputEngine::InputMode::Dialable:
            symbolCategories.append(DECUMA_CATEGORY_PHONE_NUMBER);
            break;

        case QVirtualKeyboardInputEngine::InputMode::Greek:
            symbolCategories.append(DECUMA_CATEGORY_GREEK);
            symbolCategories.append(DECUMA_CATEGORY_QUEST_EXCL_MARK_PUNCTUATIONS);
            symbolCategories.append(DECUMA_CATEGORY_PERIOD_COMMA_PUNCTUATIONS);
            symbolCategories.append(DECUMA_CATEGORY_COLON_PUNCTUATIONS);
            symbolCategories.append(DECUMA_CATEGORY_CONTRACTION_MARK);
            symbolCategories.append(DECUMA_CATEGORY_CONTRACTION_MARK);
            break;

        case QVirtualKeyboardInputEngine::InputMode::Cyrillic:
            symbolCategories.append(DECUMA_CATEGORY_CYRILLIC);
            symbolCategories.append(DECUMA_CATEGORY_QUEST_EXCL_MARK_PUNCTUATIONS);
            symbolCategories.append(DECUMA_CATEGORY_PERIOD_COMMA_PUNCTUATIONS);
            // Ukrainian needs contraction mark, but not Russian or Bulgarian
            if (language == DECUMA_LANG_UK)
                symbolCategories.append(DECUMA_CATEGORY_CONTRACTION_MARK);
            break;

        case QVirtualKeyboardInputEngine::InputMode::Arabic:
            symbolCategories.append(DECUMA_CATEGORY_ARABIC_ISOLATED_LETTER_MODE);
            symbolCategories.append(DECUMA_CATEGORY_ARABIC_GESTURES);
            leftToRightGestures = false;
            break;

        case QVirtualKeyboardInputEngine::InputMode::Hebrew:
            symbolCategories.append(DECUMA_CATEGORY_HEBREW_GL_HEBREW_CURSIVE_MODE);
            symbolCategories.append(DECUMA_CATEGORY_HEBREW_GL_HEBREW_LETTERSYMBOLS);
            symbolCategories.append(DECUMA_CATEGORY_HEBREW_SHEQEL);
            symbolCategories.append(DECUMA_CATEGORY_ARABIC_GESTURES);
            leftToRightGestures = false;
            break;

        case QVirtualKeyboardInputEngine::InputMode::Thai:
            symbolCategories.append(DECUMA_CATEGORY_THAI_BASE);
            symbolCategories.append(DECUMA_CATEGORY_THAI_NON_BASE);
            break;

        default:
            qCCritical(lcT9Write)  << "Invalid input mode" << inputMode;
            return false;
        }

        if (leftToRightGestures) {
            symbolCategories.append(DECUMA_CATEGORY_BACKSPACE_STROKE);
            symbolCategories.append(DECUMA_CATEGORY_RETURN_STROKE);
            symbolCategories.append(DECUMA_CATEGORY_WHITESPACE_STROKE);
        }

        return true;
    }

    bool updateSymbolCategoriesCjk(DECUMA_UINT32 language, const QLocale &locale,
                                   QVirtualKeyboardInputEngine::InputMode inputMode)
    {
        Q_ASSERT(cjk);

        symbolCategories.clear();

        switch (inputMode) {
        case QVirtualKeyboardInputEngine::InputMode::Latin:
            symbolCategories.append(DECUMA_CATEGORY_ANSI);
            symbolCategories.append(DECUMA_CATEGORY_CJK_SYMBOL);
            symbolCategories.append(DECUMA_CATEGORY_PUNCTUATIONS);
            break;

        case QVirtualKeyboardInputEngine::InputMode::Numeric:
            symbolCategories.append(DECUMA_CATEGORY_DIGIT);
            symbolCategories.append(DECUMA_CATEGORY_CJK_SYMBOL);
            symbolCategories.append(DECUMA_CATEGORY_PUNCTUATIONS);
            break;

        case QVirtualKeyboardInputEngine::InputMode::Dialable:
            symbolCategories.append(DECUMA_CATEGORY_DIGIT);
            symbolCategories.append(DECUMA_CATEGORY_CJK_SYMBOL);
            break;

        case QVirtualKeyboardInputEngine::InputMode::ChineseHandwriting:
            switch (locale.script()) {
            case QLocale::SimplifiedChineseScript:
                symbolCategories.append(DECUMA_CATEGORY_GB2312_A);
                symbolCategories.append(DECUMA_CATEGORY_GB2312_B_CHARS_ONLY);
                symbolCategories.append(DECUMA_CATEGORY_GBK_3);
                symbolCategories.append(DECUMA_CATEGORY_GBK_4);
                symbolCategories.append(DECUMA_CATEGORY_CJK_SYMBOL);
                symbolCategories.append(DECUMA_CATEGORY_CJK_GENERAL_PUNCTUATIONS);
                symbolCategories.append(DECUMA_CATEGORY_PUNCTUATIONS);
#ifdef HAVE_XT9
                if (xt9Ime) {
                    symbolCategories.append(DECUMA_CATEGORY_ANSI);
                }
#endif
                break;

            case QLocale::TraditionalChineseScript:
                symbolCategories.append(DECUMA_CATEGORY_BIGFIVE);
                if (language == DECUMA_LANG_HK)
                    symbolCategories.append(DECUMA_CATEGORY_HKSCS_CHARS_ONLY);
                symbolCategories.append(DECUMA_CATEGORY_CJK_SYMBOL);
                symbolCategories.append(DECUMA_CATEGORY_CJK_GENERAL_PUNCTUATIONS);
                symbolCategories.append(DECUMA_CATEGORY_PUNCTUATIONS);
                break;

            default:
                qCCritical(lcT9Write)  << "Invalid locale" << locale << "for" << engineModeToString(engineMode);
                return false;
            }
            break;

        case QVirtualKeyboardInputEngine::InputMode::JapaneseHandwriting:
            symbolCategories.append(DECUMA_CATEGORY_JIS_LEVEL_1);
            symbolCategories.append(DECUMA_CATEGORY_JIS_LEVEL_2);
            symbolCategories.append(DECUMA_CATEGORY_HIRAGANA);
            symbolCategories.append(DECUMA_CATEGORY_KATAKANA);
            symbolCategories.append(DECUMA_CATEGORY_HIRAGANASMALL);
            symbolCategories.append(DECUMA_CATEGORY_KATAKANASMALL);
            symbolCategories.append(DECUMA_CATEGORY_CJK_SYMBOL);
            symbolCategories.append(DECUMA_CATEGORY_CJK_GENERAL_PUNCTUATIONS);
            symbolCategories.append(DECUMA_CATEGORY_PUNCTUATIONS);
#ifdef HAVE_XT9
            if (xt9Ime) {
                symbolCategories.append(DECUMA_CATEGORY_ANSI);
            }
#endif
            break;

        case QVirtualKeyboardInputEngine::InputMode::KoreanHandwriting:
            symbolCategories.append(DECUMA_CATEGORY_HANGUL_1001_A);
            symbolCategories.append(DECUMA_CATEGORY_HANGUL_1001_B);
            symbolCategories.append(DECUMA_CATEGORY_CJK_SYMBOL);
            symbolCategories.append(DECUMA_CATEGORY_CJK_GENERAL_PUNCTUATIONS);
            symbolCategories.append(DECUMA_CATEGORY_PUNCTUATIONS);
            break;

        default:
            return false;
        }

        return true;
    }

    void updateDictionary(DECUMA_UINT32 language, const QLocale &locale, bool languageChanged)
    {
        Q_Q(T9WriteInputMethod);

        /*  The dictionary is loaded in the background thread. Once the loading is
            complete the dictionary will be attached to the current session. The
            attachment happens in the worker thread context, thus the direct
            connection for the signal handler and the mutex protecting the
            converted dictionary for concurrent access.
            The loading operation is blocking for the main thread only if the
            user starts handwriting input before the operation is complete.
        */
        const std::lock_guard<QRecursiveMutex> dictionaryGuard(dictionaryLock);

        // Detach previous dictionary if the language is being changed
        // or the recognizer mode is single-character mode
        const Qt::InputMethodHints inputMethodHints = q->inputContext()->inputMethodHints();
        if ((languageChanged || inputMethodHints.testFlag(Qt::ImhNoPredictiveText) || sessionSettings.recognitionMode == scrMode) && attachedDictionary) {
            detachDictionary(attachedDictionary);
            attachedDictionary.reset();
        }

        // Check if a dictionary needs to be loaded
        if (languageChanged || !loadedDictionary) {
            loadedDictionary.reset();

            DECUMA_SRC_DICTIONARY_INFO dictionaryInfo;
            memset(&dictionaryInfo, 0, sizeof(dictionaryInfo));

            QList<QLocale> decumaLocales;
            decumaLocales.append(locale);

            // CJK: No dictionary for latin input
            if (cjk && language == DECUMA_LANG_EN)
                decumaLocales.clear();

            dictionaryFileName.clear();
            QLocale decumaLocale;
            for (const QLocale &tryLocale : decumaLocales) {
                dictionaryFileName = findDictionary(tryLocale, dictionaryInfo.srcType);
                if (!dictionaryFileName.isEmpty()) {
                    decumaLocale = tryLocale;
                    break;
                }
            }
            if (!dictionaryFileName.isEmpty()) {
                if (dictionaryTask.isNull() || dictionaryTask->dictionaryFileName != dictionaryFileName) {
                    qCDebug(lcT9Write) << " -> load dictionary:" << dictionaryFileName;

                    bool convertDictionary = true;
#if defined(HAVE_CERENCE_HWR_CJK)
                    // Chinese dictionary cannot be converted (PHD)
                    if (dictionaryInfo.srcType == decumaPortableHWRDictionary && decumaLocale.language() == QLocale::Chinese)
                        convertDictionary = false;
#endif

                    QSharedPointer<T9WriteAbstractSource> sourceDictionary(new T9WriteFileSource(dictionaryInfo, dictionaryFileName));

                    QSharedPointer<T9WriteDictionary> newDictionary(new T9WriteDictionary(sourceDictionary, decumaSession, memFuncs, cjk));
                    dictionaryTask.reset(new T9WriteDictionaryTask(newDictionary, convertDictionary));

                    QObjectPrivate::connect(dictionaryTask.data(), &T9WriteDictionaryTask::completed,
                                            this, &T9WriteInputMethodPrivate::dictionaryLoadCompleted, Qt::DirectConnection);
                    worker->addTask(dictionaryTask);
                }
            }
        }

        // Attach existing dictionary, if available
        if (sessionSettings.recognitionMode != scrMode && !inputMethodHints.testFlag(Qt::ImhNoPredictiveText) &&
                loadedDictionary && !attachedDictionary) {
            if (attachDictionary(loadedDictionary))
                attachedDictionary = loadedDictionary;
        }
    }

    QByteArray getContext(QVirtualKeyboardInputEngine::PatternRecognitionMode patternRecognitionMode,
                          const QVariantMap &traceCaptureDeviceInfo,
                          const QVariantMap &traceScreenInfo) const
    {
        QCryptographicHash hash(QCryptographicHash::Md5);

        hash.addData(QByteArrayView(reinterpret_cast<const char *>(&patternRecognitionMode), sizeof(patternRecognitionMode)));

        QByteArray mapData;
        QDataStream ds(&mapData, QIODevice::WriteOnly);
        ds << traceCaptureDeviceInfo;
        ds << traceScreenInfo;
        hash.addData(mapData);

        return hash.result();
    }

    void setContext(QVirtualKeyboardInputEngine::PatternRecognitionMode patternRecognitionMode,
                    const QVariantMap &traceCaptureDeviceInfo,
                    const QVariantMap &traceScreenInfo,
                    const QByteArray &context)
    {
        Q_UNUSED(patternRecognitionMode);
        Q_UNUSED(traceScreenInfo);
        if (context == currentContext)
            return;
        currentContext = context;

        qCDebug(lcT9Write) << "T9WriteInputMethodPrivate::setContext():" << QLatin1String((context.toHex()));

        // Finish recognition, but preserve current input
        Q_Q(T9WriteInputMethod);
        QString preeditText = q->inputContext()->preeditText();
        bool preserveCurrentInput = !preeditText.isEmpty();
        T9WriteCaseFormatter oldCaseFormatter(caseFormatter);
        finishRecognition(!preserveCurrentInput);

        if (preserveCurrentInput) {
            caseFormatter = oldCaseFormatter;
            stringStart = preeditText;
            wordCandidates.append(T9WriteWordCandidate(preeditText));
            activeWordIndex = 0;
            emit q->selectionListChanged(QVirtualKeyboardSelectionListModel::Type::WordCandidateList);
            emit q->selectionListActiveItemChanged(QVirtualKeyboardSelectionListModel::Type::WordCandidateList, activeWordIndex);
        }

        const int dpi = traceCaptureDeviceInfo.value(QLatin1String("dpi"), 96).toInt();
        static const int INSTANT_GESTURE_WIDTH_THRESHOLD_MM = 25;
        gestureWidthThreshold = static_cast<DECUMA_UINT32>(INSTANT_GESTURE_WIDTH_THRESHOLD_MM / 25.4 * dpi);

        gestureRecognizer.setDpi(dpi);

        sessionSettings.baseline = 0;
        sessionSettings.helpline = 0;
        sessionSettings.topline = 0;
        sessionSettings.supportLineSet = baselineAndHelpline;
        sessionSettings.UIInputGuide = none;

        DECUMA_STATUS status = DECUMA_API(ChangeSessionSettings)(decumaSession, &sessionSettings);
        Q_ASSERT(status == decumaNoError);
    }

    QVirtualKeyboardTrace *traceBegin(
            int traceId, QVirtualKeyboardInputEngine::PatternRecognitionMode patternRecognitionMode,
            const QVariantMap &traceCaptureDeviceInfo, const QVariantMap &traceScreenInfo)
    {
        if (!worker)
            return nullptr;

        // The result id follows the trace id so that the (previous)
        // results completed during the handwriting can be rejected.
        resultId = traceId;

        stopResultTimer();

        // Dictionary must be completed before the arc addition can begin
        worker->waitForAllTasksOfType<T9WriteDictionaryTask>();
        dictionaryTask.reset();

        // Cancel the current recognition task
        worker->removeAllTasks<T9WriteRecognitionResultsTask>();
        worker->removeAllTasks<T9WriteRecognitionTask>();
        if (recognitionTask) {
            recognitionTask->cancelRecognition();
            recognitionTask.reset();
        }

        // Check for hard limit on the size the trace list
        if (traceList.size() >= traceListHardLimit) {
            worker->waitForAllTasksOfType<T9WriteAddArcTask>();
            while (traceListHardLimit < traceList.size())
                delete traceList.takeFirst();
        }

#ifdef QT_VIRTUALKEYBOARD_RECORD_TRACE_INPUT
        if (!unipenTrace)
            unipenTrace.reset(new UnipenTrace(traceCaptureDeviceInfo, traceScreenInfo));
#endif

        QByteArray context = getContext(patternRecognitionMode, traceCaptureDeviceInfo, traceScreenInfo);
        if (context != currentContext) {
            worker->waitForAllTasks();
            setContext(patternRecognitionMode, traceCaptureDeviceInfo, traceScreenInfo, context);
        }

        DECUMA_STATUS status;

        if (!arcAdditionStarted) {
            worker->waitForAllTasks();

            DECUMA_RECOGNITION_SETTINGS recSettings;
            memset(&recSettings, 0, sizeof(recSettings));

            // Boost dictionary words by default
            recSettings.boostLevel = attachedDictionary || attachedDynamicDictionaries.size() > 0 ? boostDictWords : noBoost;

            // Disable dictionary boost in UCR mode for URL and E-mail input
            // Otherwise it will completely mess input
            Q_Q(T9WriteInputMethod);
            const Qt::InputMethodHints inputMethodHints = q->inputContext()->inputMethodHints();
            if (sessionSettings.recognitionMode == ucrMode && (inputMethodHints & (Qt::ImhUrlCharactersOnly | Qt::ImhEmailCharactersOnly)))
                recSettings.boostLevel = noBoost;

            recSettings.stringCompleteness = canBeContinued;
            if (!stringStart.isEmpty())
                recSettings.pStringStart = const_cast<DECUMA_UNICODE *>(stringStart.utf16());

            status = DECUMA_API(BeginArcAddition)(decumaSession, &recSettings);
            Q_ASSERT(status == decumaNoError);
            arcAdditionStarted = true;
        }

        Q_Q(T9WriteInputMethod);
        QVirtualKeyboardTrace *trace = new QVirtualKeyboardTrace(q);
#ifdef QT_VIRTUALKEYBOARD_RECORD_TRACE_INPUT
        trace->setChannels(QStringList(QLatin1String("t")));
#endif
        traceList.append(trace);

        return trace;
    }

    void traceEnd(QVirtualKeyboardTrace *trace)
    {
        if (trace->isCanceled()) {
            traceList.removeOne(trace);
            delete trace;
        } else {
            if (cjk && countActiveTraces() == 0) {
                // For some reason gestures don't seem to work in CJK mode
                // Using our own gesture recognizer as fallback
                if (handleGesture())
                    return;
            }
            worker->addTask(QSharedPointer<T9WriteAddArcTask>(new T9WriteAddArcTask(trace)));
        }
        if (!traceList.isEmpty()) {
            Q_ASSERT(arcAdditionStarted);
            if (countActiveTraces() == 0)
                restartRecognition();
        }
    }

    int countActiveTraces() const
    {
        int count = 0;
        for (QVirtualKeyboardTrace *trace : std::as_const(traceList)) {
            if (!trace->isFinal())
                count++;
        }
        return count;
    }

    void clearTraces()
    {
        worker->waitForAllTasks();
        qDeleteAll(traceList);
        traceList.clear();
    }

    void noteSelected(int index)
    {
        if (index < 0 || index >= wordCandidates.size())
            return;

        qCDebug(lcT9Write) << "T9WriteInputMethodPrivate::noteSelected():" << index;
        const T9WriteWordCandidate &wordCandidate = wordCandidates[index];
        switch (wordCandidate.origin) {
        case T9WriteWordCandidate::Origin::T9Write:
            DECUMA_API(NoteSelectedCandidate)(decumaSession, wordCandidate.resultIndex);
            break;
#ifdef HAVE_XT9
        case T9WriteWordCandidate::Origin::XT9:
        {
            Xt9AwIme *xt9AwIme = static_cast<Xt9AwIme *>(xt9Ime.data());
            if (xt9AwIme) {
                xt9AwIme->noteWordDone(wordCandidate.symbs);
                xt9AwIme->selectWord(wordCandidate.resultIndex, true);
            }
            break;
        }
#endif
        default:
            break;
        }
    }

    void restartRecognition()
    {
        qCDebug(lcT9Write) << "T9WriteInputMethodPrivate::restartRecognition()";

        worker->removeAllTasks<T9WriteRecognitionResultsTask>();
        if (recognitionTask) {
            recognitionTask->cancelRecognition();
            recognitionTask.reset();
        }

        QSharedPointer<T9WriteRecognitionResult> recognitionResult(new T9WriteRecognitionResult(resultId, 9, 64));
        recognitionTask.reset(new T9WriteRecognitionTask(recognitionResult));
        worker->addTask(recognitionTask);

        QSharedPointer<T9WriteRecognitionResultsTask> resultsTask(new T9WriteRecognitionResultsTask(recognitionResult));
        QObjectPrivate::connect(resultsTask.data(), &T9WriteRecognitionResultsTask::resultsAvailable, this, &T9WriteInputMethodPrivate::setResultList, Qt::DirectConnection);
        worker->addTask(resultsTask);

        resetResultTimer(cjk ? Settings::instance()->hwrTimeoutForCjk() : Settings::instance()->hwrTimeoutForAlphabetic());
    }

    void waitForRecognitionResults()
    {
        if (!worker)
            return;

        qCDebug(lcT9Write) << "T9WriteInputMethodPrivate::waitForRecognitionResults()";
        worker->waitForAllTasks();
        processResultCheckTimer();
    }

    bool finishRecognition(bool emitSelectionListChanged = true)
    {
        qCDebug(lcT9Write) << "T9WriteInputMethodPrivate::finishRecognition()";
        if (!worker)
            return false;

        bool result = !traceList.isEmpty();

        Q_ASSERT(decumaSession != nullptr);

        stopResultTimer();

        worker->removeAllTasks<T9WriteAddArcTask>();
        worker->removeAllTasks<T9WriteRecognitionResultsTask>();
        if (recognitionTask) {
            recognitionTask->cancelRecognition();
            recognitionTask.reset();
            result = true;
        }
        worker->waitForAllTasks();

        clearTraces();

        if (arcAdditionStarted) {
            DECUMA_API(EndArcAddition)(decumaSession);
            arcAdditionStarted = false;
        }

        if (!wordCandidates.isEmpty()) {
            wordCandidates.clear();
            activeWordIndex = -1;
            if (emitSelectionListChanged) {
                Q_Q(T9WriteInputMethod);
                emit q->selectionListChanged(QVirtualKeyboardSelectionListModel::Type::WordCandidateList);
                emit q->selectionListActiveItemChanged(QVirtualKeyboardSelectionListModel::Type::WordCandidateList, activeWordIndex);
            }
            result = true;
        }

        stringStart.clear();
        scrResult.clear();
        caseFormatter.clear();

#ifdef QT_VIRTUALKEYBOARD_RECORD_TRACE_INPUT
        unipenTrace.reset();
#endif

        return result;
    }

    bool select(int index = -1)
    {
        if (!worker)
            return false;

        if (sessionSettings.recognitionMode != scrMode && wordCandidates.isEmpty()) {
            finishRecognition();
            return false;
        }
        if (sessionSettings.recognitionMode == scrMode && scrResult.isEmpty()) {
            finishRecognition();
            return false;
        }

        qCDebug(lcT9Write) << "T9WriteInputMethodPrivate::select():" << index;

        Q_Q(T9WriteInputMethod);
        if (sessionSettings.recognitionMode != scrMode) {
            index = index >= 0 ? index : activeWordIndex;
            noteSelected(index);
            QString finalWord = wordCandidates.at(index).symbs;
            dlmAddWord(finalWord);

#ifdef QT_VIRTUALKEYBOARD_RECORD_TRACE_INPUT
            // Record trace
            if (unipenTrace) {
                if (finalWord.length() == 1) {
                    // In recording mode, the text case must match with the current text case
                    QChar ch(finalWord.at(0));
                    if (!ch.isLetter() || (ch.isUpper() == (textCase == QVirtualKeyboardInputEngine::TextCase::Upper))) {
                        QStringList homeLocations = QStandardPaths::standardLocations(QStandardPaths::HomeLocation);
                        if (!homeLocations.isEmpty()) {
                            unipenTrace->setDirectory(QStringLiteral("%1/%2").arg(homeLocations.at(0)).arg(QLatin1String("VIRTUAL_KEYBOARD_TRACES")));
                            unipenTrace->record(traceList);
                            unipenTrace->save(ch.unicode(), 100);
                        }
                    }
                }
            }
#endif

            finishRecognition();
            QChar gesture = T9WriteInputMethodPrivate::mapSymbolToGesture(finalWord.right(1).at(0));
            if (!gesture.isNull())
                finalWord.chop(1);
            q->inputContext()->commit(finalWord);
            applyGesture(gesture);
        } else if (sessionSettings.recognitionMode == scrMode) {
            QString finalWord = scrResult;
            finishRecognition();
            q->inputContext()->inputEngine()->virtualKeyClick(static_cast<Qt::Key>(finalWord.at(0).unicode()), finalWord, Qt::NoModifier);
        }

        return true;
    }

    void resetResultTimer(int interval = 500)
    {
        qCDebug(lcT9Write) << "T9WriteInputMethodPrivate::resetResultTimer():" << interval;
        Q_Q(T9WriteInputMethod);
        stopResultTimer();
        resultTimer = q->startTimer(interval);
    }

    void stopResultTimer()
    {
        if (resultTimer) {
            qCDebug(lcT9Write) << "T9WriteInputMethodPrivate::stopResultTimer()";
            Q_Q(T9WriteInputMethod);
            q->killTimer(resultTimer);
            resultTimer = 0;
        }
    }

    void dictionaryLoadCompleted(QSharedPointer<T9WriteAbstractDictionary> dictionary)
    {
        // Note: This method is called in worker thread context
        const std::lock_guard<QRecursiveMutex> dictionaryGuard(dictionaryLock);

        if (!dictionary)
            return;

        qCDebug(lcT9Write) << "T9WriteInputMethodPrivate::dictionaryLoadCompleted():"
                           << dictionary->name() << dictionary->data() << dictionary->size();

        Q_Q(T9WriteInputMethod);
        QVirtualKeyboardInputContext *ic = q->inputContext();
        if (ic && dictionary->name() == dictionaryFileName) {
            loadedDictionary = dictionary;
            if (sessionSettings.recognitionMode != scrMode &&
                    !ic->inputMethodHints().testFlag(Qt::ImhNoPredictiveText) &&
                    !attachedDictionary) {
                if (attachDictionary(loadedDictionary))
                    attachedDictionary = loadedDictionary;
            }
        }
    }

    void recognitionError(int status)
    {
        qCDebug(lcT9Write) << "T9WriteInputMethodPrivate::recognitionError():" << status;
        Q_Q(T9WriteInputMethod);
        q->reset();
    }

    // Note: Called from T9WriteWorker thread!
    void setResultList(const QVariantList &resultList)
    {
        {
            const std::lock_guard<QRecursiveMutex> ListGuard(resultListLock);
            this->resultList = resultList;
        }

        Q_Q(T9WriteInputMethod);
        emit q->resultListChanged();
    }

    void processResultCheckTimer()
    {
        bool resultTimerWasRunning = resultTimer != 0;

        processResult();

        // Restart the result timer now if it stopped before the results were completed
        if (!resultTimerWasRunning && (!scrResult.isEmpty() || !wordCandidates.isEmpty()))
            resetResultTimer(0);
    }

    void processResult()
    {
        qCDebug(lcT9Write) << "T9WriteInputMethodPrivate::processResult()";

#ifdef SENSITIVE_DEBUG
        if (lcT9Write().isDebugEnabled()) {
            const std::lock_guard<QRecursiveMutex> resultListGuard(resultListLock);
            for (int i = 0; i < resultList.size(); i++) {
                QVariantMap result = resultList.at(i).toMap();
                QString resultPrint = QStringLiteral("%1: ").arg(i + 1);
                QString resultChars = result.value(QLatin1String("chars")).toString();
                if (!resultChars.isEmpty())
                    resultPrint.append(resultChars);
                if (result.contains(QLatin1String("gesture"))) {
                    if (!resultChars.isEmpty())
                        resultPrint.append(QLatin1String(", "));
                    QString gesture = result[QLatin1String("gesture")].toString();
                    resultPrint.append(QLatin1String("gesture ="));
                    for (const QChar &chr : gesture) {
                        resultPrint.append(QString::fromLatin1(" 0x%1").arg(chr.unicode(), 0, 16));
                    }
                }
                qCDebug(lcT9Write) << resultPrint.toUtf8().constData();
            }
        }
#endif

        Q_Q(T9WriteInputMethod);
        QVirtualKeyboardInputContext *ic = q->inputContext();
        if (!ic)
            return;

#ifdef HAVE_XT9
        int xt9DefaultListIndex = 0;
        QStringList xt9Candidates;
#endif

        QList<T9WriteWordCandidate> newWordCandidates;
        int newActiveWordIndex = -1;
        QString resultString;
        QString gesture;
        QVariantList symbolStrokes;
        {
            const std::lock_guard<QRecursiveMutex> resultListGuard(resultListLock);
            if (resultList.isEmpty())
                return;

            if (resultList.first().toMap()[QLatin1String("resultId")] != resultId) {
                qCDebug(lcT9Write) << "T9WriteInputMethodPrivate::processResult(): resultId mismatch" << resultList.first().toMap()[QLatin1String("resultId")] << "(" << resultId << ")";
                resultList.clear();
                return;
            }
            lastResultId = resultId;

            for (int i = 0; i < resultList.size(); i++) {
                QVariantMap result = resultList.at(i).toMap();
                QString resultChars = result[QLatin1String("chars")].toString();
                if (i == 0) {
                    if (ic->isShiftActive()) {
                        caseFormatter.ensureLength(1, textCase);
                        caseFormatter.ensureLength(resultChars.length(), QVirtualKeyboardInputEngine::TextCase::Lower);
                    } else {
                        caseFormatter.ensureLength(resultChars.length(), textCase);
                    }
                }
                if (!resultChars.isEmpty()) {
                    resultChars = caseFormatter.formatString(resultChars);
                    if (sessionSettings.recognitionMode != scrMode && !newWordCandidates.contains(T9WriteWordCandidate(resultChars))) {
                        newWordCandidates.append(T9WriteWordCandidate(resultChars, i, T9WriteWordCandidate::Origin::T9Write));
                    }
                }
                if (i == 0) {
                    resultString = resultChars;
                    if (result.contains(QLatin1String("gesture")))
                        gesture = result[QLatin1String("gesture")].toString();
                    if (sessionSettings.recognitionMode != scrMode && result.contains(QLatin1String("symbolStrokes")))
                        symbolStrokes = result[QLatin1String("symbolStrokes")].toList();
                    if (sessionSettings.recognitionMode == scrMode)
                        break;
#ifdef HAVE_XT9
                    xt9Candidates = xt9BuildSelectionList(resultString, &xt9DefaultListIndex);
#endif
                } else {
                    // Add a gesture symbol to the secondary candidate
                    if (sessionSettings.recognitionMode != scrMode && result.contains(QLatin1String("gesture"))) {
                        QString gesture2 = result[QLatin1String("gesture")].toString();
                        if (gesture2.length() == 1) {
                            QChar symbol = T9WriteInputMethodPrivate::mapGestureToSymbol(gesture2.at(0).unicode());
                            if (!symbol.isNull()) {
                                // Check for duplicates
                                bool duplicateFound = false;
                                for (const T9WriteWordCandidate &wordCandidate : newWordCandidates) {
                                    duplicateFound = wordCandidate.symbs.size() == 1 && wordCandidate.symbs.at(0) == symbol;
                                    if (duplicateFound)
                                        break;
                                }
                                if (!duplicateFound) {
                                    if (!resultChars.isEmpty()) {
                                        newWordCandidates.last().symbs.append(symbol);
                                    } else {
                                        newWordCandidates.append(T9WriteWordCandidate(symbol, i, T9WriteWordCandidate::Origin::T9Write));
                                    }
                                }
                            }
                        }
                    }
#ifdef HAVE_XT9
                    if (i >= 2 && !xt9Candidates.isEmpty())
                        break;
#endif
                }
            }

            resultList.clear();

            if (!newWordCandidates.isEmpty())
                newActiveWordIndex = 0;
#ifdef HAVE_XT9
            if (!xt9Candidates.isEmpty())
                appendWordCandidates(newWordCandidates, newActiveWordIndex, resultString, xt9Candidates, xt9DefaultListIndex, T9WriteWordCandidate::Origin::XT9);
#endif
        }

        bool wordCandidatesChanged = true;

#ifndef QT_VIRTUALKEYBOARD_RECORD_TRACE_INPUT
        // Delete trace history
        // Note: We have to be sure there are no background tasks
        //       running since the QVirtualKeyboardTrace objects consumed there.
        if (worker->numberOfPendingTasks() == 0) {

            const QVirtualKeyboardInputEngine::InputMode inputMode = q->inputEngine()->inputMode();
            if (sessionSettings.recognitionMode != scrMode &&
                    inputMode != QVirtualKeyboardInputEngine::InputMode::ChineseHandwriting &&
                    inputMode != QVirtualKeyboardInputEngine::InputMode::JapaneseHandwriting &&
                    inputMode != QVirtualKeyboardInputEngine::InputMode::KoreanHandwriting) {
                const int hwrTimeout = cjk ?
                            Settings::instance()->hwrTimeoutForCjk() :
                            Settings::instance()->hwrTimeoutForAlphabetic();
                for (int traceIndex = 0; traceIndex < traceList.size();) {
                    QVirtualKeyboardTrace *trace = traceList.at(traceIndex);
                    if (trace->opacity() > 0) {
                        trace->startHideTimer(hwrTimeout);
                        ++traceIndex;
                    } else {
                        traceList.removeAt(traceIndex);
                        delete trace;
                    }
                }
            }

            // Enforce hard limit for number of traces
            if (traceList.size() >= traceListHardLimit) {
                qCDebug(lcT9Write) << "T9WriteInputMethodPrivate::processResult(): Clearing traces (hard limit):" << traceList.size();
                clearTraces();
            }
        }
#endif

        // Find a gesture at the end of the first result
        if (!gesture.isEmpty()) {

            DECUMA_UNICODE gestureSymbol = gesture.at(0).unicode();
            if (!applyGesture(gestureSymbol)) {
                ic->commit(ic->preeditText());
                finishRecognition();
            }

            return;
        }

        if (sessionSettings.recognitionMode != scrMode) {
            ignoreUpdate = true;
            ic->setPreeditText(resultString);
            ignoreUpdate = false;
        } else {
            scrResult = resultString;
        }

        if (wordCandidatesChanged) {
            wordCandidates = newWordCandidates;
            activeWordIndex = wordCandidates.isEmpty() ? -1 : newActiveWordIndex;
            emit q->selectionListChanged(QVirtualKeyboardSelectionListModel::Type::WordCandidateList);
            emit q->selectionListActiveItemChanged(QVirtualKeyboardSelectionListModel::Type::WordCandidateList, activeWordIndex);
        }

        if (arcAdditionStarted && traceList.isEmpty() && worker->numberOfPendingTasks() == 0) {
            DECUMA_API(EndArcAddition)(decumaSession);
            arcAdditionStarted = false;
        }
    }

    static QChar mapGestureToSymbol(const QChar &gesture)
    {
        switch (gesture.unicode()) {
        case '\r':
            return QChar(0x23CE);
        case ' ':
            return QChar(0x2423);
        default:
            return QChar();
        }
    }

    static QChar mapSymbolToGesture(const QChar &symbol)
    {
        switch (symbol.unicode()) {
        case 0x23CE:
            return QLatin1Char('\r');
        case 0x2423:
            return QLatin1Char(' ');
        default:
            return QChar();
        }
    }

    bool applyGesture(const QChar &gesture)
    {
        Q_Q(T9WriteInputMethod);
        QVirtualKeyboardInputContext *ic = q->inputContext();
        switch (gesture.unicode()) {
        case '\b':
            return ic->inputEngine()->virtualKeyClick(Qt::Key_Backspace, QString(), Qt::NoModifier);
        case '\r':
            return ic->inputEngine()->virtualKeyClick(Qt::Key_Return, QLatin1String("\n"), Qt::NoModifier);
        case ' ':
            return ic->inputEngine()->virtualKeyClick(Qt::Key_Space, QLatin1String(" "), Qt::NoModifier);
        default:
            return false;
        }
    }

    bool handleGesture()
    {
        if (countActiveTraces() > 0)
            return false;

        QVariantMap gesture(gestureRecognizer.recognize(traceList.mid(traceList.size() - 1, 1)));
        if (gesture.isEmpty())
            return false;

        qCDebug(lcT9Write) << "T9WriteInputMethodPrivate::handleGesture():" << gesture;

        if (gesture[QLatin1String("type")].toString() == QLatin1String("swipe")) {

            static const int SWIPE_ANGLE_THRESHOLD = 15;    // degrees +-

            qreal swipeLength = gesture[QLatin1String("length")].toReal();
            if (swipeLength >= gestureWidthThreshold) {

                Q_Q(T9WriteInputMethod);
                QVirtualKeyboardInputContext *ic = q->inputContext();
                if (!ic)
                    return false;

                qreal swipeAngle = gesture[QLatin1String("angle_degrees")].toReal();
                int swipeTouchCount = gesture[QLatin1String("touch_count")].toInt();

                // Swipe left
                if (swipeAngle <= 180 + SWIPE_ANGLE_THRESHOLD && swipeAngle >= 180 - SWIPE_ANGLE_THRESHOLD) {
                    if (swipeTouchCount == 1) {
                        // Single swipe: backspace
                        ic->inputEngine()->virtualKeyClick(Qt::Key_Backspace, QString(), Qt::NoModifier);
                        return true;
                    }
                    return false;
                }

                // Swipe right
                const QVirtualKeyboardInputEngine::InputMode inputMode = q->inputEngine()->inputMode();
                if (inputMode != QVirtualKeyboardInputEngine::InputMode::ChineseHandwriting &&
                        inputMode != QVirtualKeyboardInputEngine::InputMode::JapaneseHandwriting &&
                        inputMode != QVirtualKeyboardInputEngine::InputMode::KoreanHandwriting) {
                    if (swipeAngle <= SWIPE_ANGLE_THRESHOLD || swipeAngle >= 360 - SWIPE_ANGLE_THRESHOLD) {
                        if (swipeTouchCount == 1) {
                            // Single swipe: space
                            ic->inputEngine()->virtualKeyClick(Qt::Key_Space, QLatin1String(" "), Qt::NoModifier);
                            return true;
                        }
                        return false;
                    }
                }

                // Swipe up
                if (swipeAngle <= 270 + SWIPE_ANGLE_THRESHOLD && swipeAngle >= 270 - SWIPE_ANGLE_THRESHOLD) {
                    if (swipeTouchCount == 1) {
                        // Single swipe: toggle input mode
                        select();
                        if (!(ic->inputMethodHints() & (Qt::ImhDialableCharactersOnly | Qt::ImhFormattedNumbersOnly | Qt::ImhDigitsOnly))) {
                            QList<int> inputModes = ic->inputEngine()->inputModes();
                            // Filter out duplicate numeric mode (in favor of Numeric)
                            int indexOfNumericInputMode = inputModes.indexOf(static_cast<const int>(QVirtualKeyboardInputEngine::InputMode::Numeric));
                            int indexOfDialableInputMode = inputModes.indexOf(static_cast<const int>(QVirtualKeyboardInputEngine::InputMode::Dialable));
                            if (indexOfNumericInputMode != -1 && indexOfDialableInputMode != -1)
                                inputModes.removeAt(inputMode != QVirtualKeyboardInputEngine::InputMode::Dialable ?
                                            indexOfDialableInputMode :
                                            indexOfNumericInputMode);
                            if (inputModes.size() > 1) {
                                int inputModeIndex = inputModes.indexOf(static_cast<const int>(inputMode)) + 1;
                                if (inputModeIndex >= inputModes.size())
                                    inputModeIndex = 0;
                                ic->inputEngine()->setInputMode(static_cast<QVirtualKeyboardInputEngine::InputMode>(inputModes.at(inputModeIndex)));
                            }
                        }
                        return true;
                    }
                }
            }
        }

        return false;
    }

    bool isValidInputChar(const QChar &c) const
    {
        if (c.isLetterOrNumber())
            return true;
        if (isJoiner(c))
            return true;
        return false;
    }

    bool isJoiner(const QChar &c) const
    {
        if (c.isPunct() || c.isSymbol()) {
            Q_Q(const T9WriteInputMethod);
            QVirtualKeyboardInputContext *ic = q->inputContext();
            if (ic) {
                Qt::InputMethodHints inputMethodHints = ic->inputMethodHints();
                if (inputMethodHints.testFlag(Qt::ImhUrlCharactersOnly) || inputMethodHints.testFlag(Qt::ImhEmailCharactersOnly))
                    return QString(QStringLiteral(":/?#[]@!$&'()*+,;=-_.%")).contains(c);
            }
            ushort unicode = c.unicode();
            if (unicode == Qt::Key_Apostrophe || unicode == Qt::Key_Minus)
                return true;
        }
        return false;
    }

    void onAvailableDynamicDictionariesChanged()
    {
        if (!worker)
            return;

        const std::lock_guard<QRecursiveMutex> dictionaryGuard(dictionaryLock);
        QVirtualKeyboardDictionaryManager *dictionaryManager = QVirtualKeyboardDictionaryManager::instance();

        const QStringList availableDictionaries = dictionaryManager->availableDictionaries();
        for (const QString &dictionaryName : availableDictionaries) {

            if (!dynamicDictionaries.contains(dictionaryName)) {

                DECUMA_SRC_DICTIONARY_INFO sourceInfo;
                sourceInfo.srcType = decumaTextList;
                sourceInfo.bNoFrequencyRanking = 1;
                sourceInfo.multiStepWordSeparator = 0;

                QSharedPointer<T9WriteAbstractSource> sourceDictionary(
                            new T9WriteStringSource(
                                sourceInfo,
                                dictionaryManager->dictionary(dictionaryName)->contents(),
                                dictionaryName));

                QSharedPointer<T9WriteDictionary> dynamicDictionary(
                            new T9WriteDictionary(
                                sourceDictionary,
                                decumaSession,
                                memFuncs,
                                cjk));

                dynamicDictionaries[dictionaryName] = dynamicDictionary;

                QSharedPointer<T9WriteDictionaryTask> dynamicDictionaryTask(
                            new T9WriteDictionaryTask(
                                dynamicDictionary,
                                true));

                Q_Q(T9WriteInputMethod);
                q->connect(dynamicDictionaryTask.data(),
                           &T9WriteDictionaryTask::completed,
                           [=](QSharedPointer<T9WriteAbstractDictionary> dynamicDictionary) {

                    const std::lock_guard<QRecursiveMutex> dictionaryGuard(dictionaryLock);

                    if (dynamicDictionary->data()) {
                        if (dictionaryManager->activeDictionaries().contains(dictionaryName) &&
                                !attachedDynamicDictionaries.contains(dictionaryName) &&
                                attachDictionary(dynamicDictionary))
                            attachedDynamicDictionaries[dictionaryName] = dynamicDictionary;
                    } else {
                        dynamicDictionaries.remove(dictionaryName);
                    }
                });

                worker->addTask(dynamicDictionaryTask);
            }

#ifdef HAVE_XT9
            if (!xt9DynamicDictionaries.contains(dictionaryName)) {
                if (xt9Ime) {
                    QVirtualKeyboardDictionary *dictionary = dictionaryManager->dictionary(dictionaryName);
                    const quint16 id = static_cast<quint16>(xt9DynamicDictionaryNextId.fetchAndAddRelaxed(1));
                    xt9DynamicDictionaries[dictionaryName] = id;

                    xt9Ime->updateIndex(id, dictionary->contents());

                    Q_Q(T9WriteInputMethod);
                    q->connect(dictionary, &QVirtualKeyboardDictionary::contentsChanged, q, [=]() {
                        xt9Ime->updateIndex(id, dictionary->contents());
                        if (xt9AttachedDynamicDictionaries.contains(dictionaryName))
                            xt9Ime->mountIndex(id);
                    });
                }
            }
#endif
        }
    }

    void onActiveDynamicDictionariesChanged()
    {
        if (!worker)
            return;

        const std::lock_guard<QRecursiveMutex> dictionaryGuard(dictionaryLock);
        QVirtualKeyboardDictionaryManager *dictionaryManager = QVirtualKeyboardDictionaryManager::instance();

        // Attach
        const QStringList activeDictionaries = dictionaryManager->activeDictionaries();
        for (const QString &dictionaryName : activeDictionaries) {

            QSharedPointer<T9WriteAbstractDictionary> dynamicDictionary = dynamicDictionaries.value(dictionaryName);
            if (dynamicDictionary && dynamicDictionary->data() &&
                    !attachedDynamicDictionaries.contains(dictionaryName) &&
                    dynamicDictionary->isCompleted() &&
                    attachDictionary(dynamicDictionary)) {
                attachedDynamicDictionaries[dictionaryName] = dynamicDictionary;
            }
#ifdef HAVE_XT9
            if (xt9Ime) {
                if (!xt9AttachedDynamicDictionaries.contains(dictionaryName)) {
                    xt9AttachDictionary(dictionaryName);
                }
            }
#endif
        }

        // Detach
        const QStringList attachedDynamicDictionariesKeys = attachedDynamicDictionaries.keys();
        for (const QString &dictionaryName : attachedDynamicDictionariesKeys) {
            if (!activeDictionaries.contains(dictionaryName)) {
                if (attachedDynamicDictionaries.contains(dictionaryName)) {
                    detachDictionary(attachedDynamicDictionaries[dictionaryName]);
                    attachedDynamicDictionaries.remove(dictionaryName);
                }
            }
        }
#ifdef HAVE_XT9
        // Detach (XT9)
        if (xt9Ime) {
            const QStringList xt9AttachedDynamicDictionariesKeys = xt9AttachedDynamicDictionaries.keys();
            for (const QString &dictionaryName : xt9AttachedDynamicDictionariesKeys) {
                if (!activeDictionaries.contains(dictionaryName)) {
                    xt9DetachDictionary(dictionaryName);
                }
            }
        }
#endif
    }

    bool isDlmActive()
    {
        const std::lock_guard<QRecursiveMutex> dictionaryGuard(dictionaryLock);
        return !loadedDlmDictionary.isNull();
    }

    QString dlmFileName() const
    {
        QString suffix;
        switch (engineMode) {
        case T9WriteInputMethod::EngineMode::Alphabetic:
        case T9WriteInputMethod::EngineMode::Arabic:
        case T9WriteInputMethod::EngineMode::Hebrew:
        case T9WriteInputMethod::EngineMode::Thai:
            suffix = QStringLiteral("aw");
            break;
        case T9WriteInputMethod::EngineMode::SimplifiedChinese:
        case T9WriteInputMethod::EngineMode::TraditionalChinese:
        case T9WriteInputMethod::EngineMode::HongKongChinese:
            suffix = QStringLiteral("cp");
            break;
        case T9WriteInputMethod::EngineMode::Japanese:
            suffix = QStringLiteral("j");
            break;
        case T9WriteInputMethod::EngineMode::Korean:
            suffix = QStringLiteral("k");
            break;
        default:
            break;
        }
        return QStringLiteral("cerence-hwr%1.dlm").arg(suffix);
    }

    void dlmActivate()
    {
        qCDebug(lcT9Write) << "T9WriteInputMethodPrivate::dlmActivate()";

        const std::lock_guard<QRecursiveMutex> dictionaryGuard(dictionaryLock);
        if (loadedDlmDictionary)
            return;

        DECUMA_SRC_DICTIONARY_INFO sourceInfo;
        sourceInfo.srcType = decumaPortableHWRDictionary;
        sourceInfo.bNoFrequencyRanking = 1;
        sourceInfo.multiStepWordSeparator = 0;

        QString dictionaryName(QStringLiteral("%1/%2").arg(Settings::instance()->userDataPath(), dlmFileName()));
        QSharedPointer<T9WriteAbstractSource> sourceDictionary(
                    new T9WriteFileSource(
                        sourceInfo,
                        dictionaryName));

        loadedDlmDictionary.reset(new T9WriteDynamicDictionary(
                        sourceDictionary,
                        CERENCE_HWR_DLM_MAX_WORDS,
                        memFuncs,
                        cjk));

        QSharedPointer<T9WriteDictionaryTask> dynamicDictionaryTask(
                    new T9WriteDictionaryTask(
                        loadedDlmDictionary,
                        false));

        Q_Q(T9WriteInputMethod);
        q->connect(dynamicDictionaryTask.data(),
                   &T9WriteDictionaryTask::completed,
                   [=](QSharedPointer<T9WriteAbstractDictionary> dynamicDictionary) {

            const std::lock_guard<QRecursiveMutex> dictionaryGuard(dictionaryLock);

            if (!loadedDlmDictionary || dynamicDictionary != loadedDlmDictionary)
                return;

            if (dynamicDictionary->data()) {
                if (attachedDlmDictionary != dynamicDictionary &&
                        attachDictionary(dynamicDictionary)) {
                    attachedDlmDictionary = dynamicDictionary;
                }
            } else {
                dlmDeactivate();
            }
        });

        worker->addTask(dynamicDictionaryTask);
    }

    void dlmDeactivate()
    {
        const std::lock_guard<QRecursiveMutex> dictionaryGuard(dictionaryLock);

        if (loadedDlmDictionary) {
            qCDebug(lcT9Write) << "T9WriteInputMethodPrivate::dlmDeactivate()";
            loadedDlmDictionary.reset();
        }

        if (attachedDlmDictionary) {
            detachDictionary(attachedDlmDictionary);
            attachedDlmDictionary.reset();
        }
    }

    void dlmAddWord(const QString &word)
    {
        if (!isDlmActive() || !worker)
            return;

        qCDebug(lcT9Write) << "T9WriteInputMethodPrivate::dlmAddWord()";

        QSharedPointer<T9WriteDlmWordTask> learnWordTask(new T9WriteDlmWordTask(loadedDlmDictionary, word, stringStart));
        worker->addTask(learnWordTask);
    }

    bool dlmHasWord(const QString &word)
    {
        if (!isDlmActive() || !worker)
            return false;

        worker->waitForAllTasks();

        const std::lock_guard<QRecursiveMutex> dictionaryGuard(dictionaryLock);
        T9WriteDynamicDictionary *dictionary = static_cast<T9WriteDynamicDictionary *>(loadedDlmDictionary.data());

        return dictionary->hasWord(word);
    }

    void dlmRemoveWord(const QString &word)
    {
        qCDebug(lcT9Write) << "T9WriteInputMethodPrivate::dlmRemoveWord()";

        QSharedPointer<T9WriteDlmRemoveWordTask> removeWordTask(new T9WriteDlmRemoveWordTask(loadedDlmDictionary, word));
        worker->addTask(removeWordTask);
    }

    T9WriteInputMethod *q_ptr;
    static const DECUMA_MEM_FUNCTIONS memFuncs;
    bool cjk;
    T9WriteInputMethod::EngineMode engineMode;
    QByteArray currentContext;
    DECUMA_SESSION_SETTINGS sessionSettings;
    DECUMA_UINT32 gestureWidthThreshold;
    QStringList defaultHwrDbPaths;
    QFile hwrDbFile;
    QList<DECUMA_UINT32> languageCategories;
    QList<DECUMA_UINT32> symbolCategories;
    QScopedPointer<T9WriteWorker> worker;
    QList<QVirtualKeyboardTrace *> traceList;
    int traceListHardLimit;
    QRecursiveMutex dictionaryLock;
    QString dictionaryFileName;
    QSharedPointer<T9WriteAbstractDictionary> loadedDictionary;
    QSharedPointer<T9WriteAbstractDictionary> attachedDictionary;
    QSharedPointer<Xt9LdbManager> ldbManager;
    QSharedPointer<T9WriteDictionaryTask> dictionaryTask;
    QMap<QString, QSharedPointer<T9WriteAbstractDictionary>> dynamicDictionaries;
    QMap<QString, QSharedPointer<T9WriteAbstractDictionary>> attachedDynamicDictionaries;
    QSharedPointer<T9WriteAbstractDictionary> loadedDlmDictionary;
    QSharedPointer<T9WriteAbstractDictionary> attachedDlmDictionary;
    QMetaObject::Connection availableDictionariesChangedConnection;
    QMetaObject::Connection activeDictionariesChangedConnection;
    QSharedPointer<T9WriteRecognitionTask> recognitionTask;
    QRecursiveMutex resultListLock;
    QVariantList resultList;
    QMetaObject::Connection resultListChangedConnection;
    int resultId;
    int lastResultId;
    int resultTimer;
    QByteArray session;
    DECUMA_SESSION *decumaSession;
    QList<T9WriteWordCandidate> wordCandidates;
    QString stringStart;
    QString scrResult;
    int activeWordIndex;
    bool arcAdditionStarted;
    bool ignoreUpdate;
    QVirtualKeyboardInputEngine::TextCase textCase;
    T9WriteCaseFormatter caseFormatter;
    HandwritingGestureRecognizer gestureRecognizer;
#ifdef QT_VIRTUALKEYBOARD_RECORD_TRACE_INPUT
    QScopedPointer<UnipenTrace> unipenTrace;
#endif
#ifdef HAVE_XT9
    QScopedPointer<Xt9Ime> xt9Ime;
    QMap<QString, quint16> xt9DynamicDictionaries;
    QMap<QString, quint16> xt9AttachedDynamicDictionaries;
    QAtomicInt xt9DynamicDictionaryNextId;
    QMetaObject::Connection defaultInputMethodDisabledChangedConnection;
    QMetaObject::Connection defaultDictionaryDisabledChangedConnection;
#endif
    QMetaObject::Connection userDataResetConnection;
};

const DECUMA_MEM_FUNCTIONS T9WriteInputMethodPrivate::memFuncs = {
    T9WriteInputMethodPrivate::decumaMalloc,
    T9WriteInputMethodPrivate::decumaCalloc,
    T9WriteInputMethodPrivate::decumaFree,
    nullptr
};

/*!
    \class QtVirtualKeyboard::T9WriteInputMethod
    \internal
*/

T9WriteInputMethod::T9WriteInputMethod(QObject *parent) :
    QVirtualKeyboardAbstractInputMethod(*new T9WriteInputMethodPrivate(this), parent)
{
}

T9WriteInputMethod::~T9WriteInputMethod()
{
}

void T9WriteInputMethod::clearInputMode()
{
    Q_D(T9WriteInputMethod);
    d->exitEngine();
}

QList<QVirtualKeyboardInputEngine::InputMode> T9WriteInputMethod::inputModes(const QString &locale)
{
    Q_D(T9WriteInputMethod);
    QList<QVirtualKeyboardInputEngine::InputMode> availableInputModes;
    const Qt::InputMethodHints inputMethodHints(inputContext()->inputMethodHints());
    const QLocale loc(locale);
    T9WriteInputMethod::EngineMode mode = d->mapLocaleToEngineMode(loc);

    // Add primary input mode
    switch (mode) {
#ifdef HAVE_CERENCE_HWR_ALPHABETIC
    case T9WriteInputMethod::EngineMode::Alphabetic:
        if (d->findHwrDb(T9WriteInputMethod::EngineMode::Alphabetic).isEmpty())
            return availableInputModes;
        if (!(inputMethodHints & (Qt::ImhDialableCharactersOnly | Qt::ImhFormattedNumbersOnly | Qt::ImhDigitsOnly | Qt::ImhLatinOnly))) {
            switch (loc.script()) {
            case QLocale::GreekScript:
                availableInputModes.append(QVirtualKeyboardInputEngine::InputMode::Greek);
                break;
            case QLocale::CyrillicScript:
                availableInputModes.append(QVirtualKeyboardInputEngine::InputMode::Cyrillic);
                break;
            case QLocale::ThaiScript:
                availableInputModes.append(QVirtualKeyboardInputEngine::InputMode::Thai);
                break;
            default:
                break;
            }
            availableInputModes.append(QVirtualKeyboardInputEngine::InputMode::Latin);
        }
        break;
    case T9WriteInputMethod::EngineMode::Arabic:
        if (d->findHwrDb(T9WriteInputMethod::EngineMode::Arabic).isEmpty())
            return availableInputModes;
        if (!(inputMethodHints & (Qt::ImhDialableCharactersOnly | Qt::ImhFormattedNumbersOnly | Qt::ImhDigitsOnly | Qt::ImhLatinOnly)))
            availableInputModes.append(QVirtualKeyboardInputEngine::InputMode::Arabic);
        break;
    case T9WriteInputMethod::EngineMode::Hebrew:
        if (d->findHwrDb(T9WriteInputMethod::EngineMode::Hebrew).isEmpty())
            return availableInputModes;
        if (!(inputMethodHints & (Qt::ImhDialableCharactersOnly | Qt::ImhFormattedNumbersOnly | Qt::ImhDigitsOnly | Qt::ImhLatinOnly)))
            availableInputModes.append(QVirtualKeyboardInputEngine::InputMode::Hebrew);
        break;
    case T9WriteInputMethod::EngineMode::Thai:
        if (d->findHwrDb(T9WriteInputMethod::EngineMode::Thai).isEmpty())
            return availableInputModes;
        if (!(inputMethodHints & (Qt::ImhDialableCharactersOnly | Qt::ImhFormattedNumbersOnly | Qt::ImhDigitsOnly | Qt::ImhLatinOnly)))
            availableInputModes.append(QVirtualKeyboardInputEngine::InputMode::Thai);
        break;
#endif
#ifdef HAVE_CERENCE_HWR_CJK
    case T9WriteInputMethod::EngineMode::SimplifiedChinese:
    case T9WriteInputMethod::EngineMode::TraditionalChinese:
    case T9WriteInputMethod::EngineMode::HongKongChinese:
        if (d->findHwrDb(mode).isEmpty())
            return availableInputModes;
        if (!(inputMethodHints & (Qt::ImhDialableCharactersOnly | Qt::ImhFormattedNumbersOnly | Qt::ImhDigitsOnly | Qt::ImhLatinOnly)))
            availableInputModes.append(QVirtualKeyboardInputEngine::InputMode::ChineseHandwriting);
        break;
    case T9WriteInputMethod::EngineMode::Japanese:
        if (d->findHwrDb(T9WriteInputMethod::EngineMode::Japanese).isEmpty())
            return availableInputModes;
        if (!(inputMethodHints & (Qt::ImhDialableCharactersOnly | Qt::ImhFormattedNumbersOnly | Qt::ImhDigitsOnly | Qt::ImhLatinOnly)))
            availableInputModes.append(QVirtualKeyboardInputEngine::InputMode::JapaneseHandwriting);
        break;
    case T9WriteInputMethod::EngineMode::Korean:
        if (d->findHwrDb(T9WriteInputMethod::EngineMode::Korean).isEmpty())
            return availableInputModes;
        if (!(inputMethodHints & (Qt::ImhDialableCharactersOnly | Qt::ImhFormattedNumbersOnly | Qt::ImhDigitsOnly | Qt::ImhLatinOnly)))
            availableInputModes.append(QVirtualKeyboardInputEngine::InputMode::KoreanHandwriting);
        break;
#endif
    default:
        return availableInputModes;
    }

    // Add exclusive input modes
    if (inputMethodHints.testFlag(Qt::ImhDialableCharactersOnly) || inputMethodHints.testFlag(Qt::ImhDigitsOnly)) {
        availableInputModes.append(QVirtualKeyboardInputEngine::InputMode::Dialable);
    } else if (inputMethodHints.testFlag(Qt::ImhFormattedNumbersOnly)) {
        availableInputModes.append(QVirtualKeyboardInputEngine::InputMode::Numeric);
    } else if (inputMethodHints.testFlag(Qt::ImhLatinOnly)) {
        availableInputModes.append(QVirtualKeyboardInputEngine::InputMode::Latin);
    } else {
        // Add other input modes
        Q_ASSERT(!availableInputModes.isEmpty());
        if (!availableInputModes.contains(QVirtualKeyboardInputEngine::InputMode::Latin))
            availableInputModes.append(QVirtualKeyboardInputEngine::InputMode::Latin);
        availableInputModes.append(QVirtualKeyboardInputEngine::InputMode::Numeric);
    }

    return availableInputModes;
}

bool T9WriteInputMethod::setInputMode(const QString &locale, QVirtualKeyboardInputEngine::InputMode inputMode)
{
    Q_D(T9WriteInputMethod);
    d->select();
    return d->setInputMode(QLocale(locale), inputMode);
}

bool T9WriteInputMethod::setTextCase(QVirtualKeyboardInputEngine::TextCase textCase)
{
    Q_D(T9WriteInputMethod);
    d->textCase = textCase;
    return true;
}

bool T9WriteInputMethod::keyEvent(Qt::Key key, const QString &text, Qt::KeyboardModifiers modifiers)
{
    Q_UNUSED(modifiers);
    Q_D(T9WriteInputMethod);
    switch (key) {
    case Qt::Key_Enter:
    case Qt::Key_Return:
    case Qt::Key_Tab:
    case Qt::Key_Space:
        d->select();
        update();
        break;

    case Qt::Key_Backspace:
        {
            QVirtualKeyboardInputContext *ic = inputContext();
            QString preeditText = ic->preeditText();
            if (preeditText.length() > 1) {
                preeditText.chop(1);
                ic->setPreeditText(preeditText);
                d->caseFormatter.ensureLength(preeditText.length(), d->textCase);
                T9WriteCaseFormatter caseFormatter(d->caseFormatter);
                d->finishRecognition(false);
                d->caseFormatter = caseFormatter;
                d->stringStart = preeditText;
                int xt9DefaultListIndex = 0;
                d->activeWordIndex = 0;
                d->appendWordCandidates(d->wordCandidates, d->activeWordIndex, d->stringStart, d->xt9BuildSelectionList(d->stringStart, &xt9DefaultListIndex), xt9DefaultListIndex, T9WriteWordCandidate::Origin::XT9);
                emit selectionListChanged(QVirtualKeyboardSelectionListModel::Type::WordCandidateList);
                emit selectionListActiveItemChanged(QVirtualKeyboardSelectionListModel::Type::WordCandidateList, d->activeWordIndex);
                return true;
            } else {
                bool result = !preeditText.isEmpty();
                if (result)
                    ic->clear();
                else
                    result = !d->scrResult.isEmpty();
                d->finishRecognition();
                return result;
            }
        }

    default:
        if (d->sessionSettings.recognitionMode != scrMode && text.length() > 0) {
            d->waitForRecognitionResults();
            QVirtualKeyboardInputContext *ic = inputContext();
            QString preeditText = ic->preeditText();
            QChar c = text.at(0);
            bool addToWord = d->isValidInputChar(c) && (!preeditText.isEmpty() || !d->isJoiner(c));
            if (addToWord) {
                preeditText.append(text);
                ic->setPreeditText(preeditText);
                d->caseFormatter.ensureLength(preeditText.length(), d->textCase);
                T9WriteCaseFormatter caseFormatter(d->caseFormatter);
                d->finishRecognition(false);
                d->caseFormatter = caseFormatter;
                d->stringStart = preeditText;
                d->wordCandidates.append(preeditText);
                d->activeWordIndex = 0;
                emit selectionListChanged(QVirtualKeyboardSelectionListModel::Type::WordCandidateList);
                emit selectionListActiveItemChanged(QVirtualKeyboardSelectionListModel::Type::WordCandidateList, d->activeWordIndex);
                return true;
            } else {
                ic->commit();
                d->finishRecognition();
            }
            break;
        } else if (d->sessionSettings.recognitionMode == scrMode) {
            d->finishRecognition();
        }
    }
    return false;
}

void T9WriteInputMethod::reset()
{
    Q_D(T9WriteInputMethod);
    d->finishRecognition();
    d->setInputMode(QLocale(inputContext()->locale()), inputEngine()->inputMode());
}

void T9WriteInputMethod::update()
{
    Q_D(T9WriteInputMethod);
    if (d->ignoreUpdate)
        return;
    d->select();
}

QList<QVirtualKeyboardSelectionListModel::Type> T9WriteInputMethod::selectionLists()
{
    return QList<QVirtualKeyboardSelectionListModel::Type>() << QVirtualKeyboardSelectionListModel::Type::WordCandidateList;
}

int T9WriteInputMethod::selectionListItemCount(QVirtualKeyboardSelectionListModel::Type type)
{
    Q_UNUSED(type);
    Q_D(T9WriteInputMethod);
    return d->wordCandidates.size();
}

QVariant T9WriteInputMethod::selectionListData(QVirtualKeyboardSelectionListModel::Type type, int index, QVirtualKeyboardSelectionListModel::Role role)
{
    QVariant result;
    Q_D(T9WriteInputMethod);
    switch (role) {
    case QVirtualKeyboardSelectionListModel::Role::Display:
        result = QVariant(d->wordCandidates.at(index).symbs);
        break;
    case QVirtualKeyboardSelectionListModel::Role::WordCompletionLength:
        result.setValue(0);
        break;
    case QVirtualKeyboardSelectionListModel::Role::Dictionary:
    {
        QVirtualKeyboardSelectionListModel::DictionaryType dictionaryType =
                d->dlmHasWord(d->wordCandidates.at(index).symbs) ?
                    QVirtualKeyboardSelectionListModel::DictionaryType::User :
                    QVirtualKeyboardSelectionListModel::DictionaryType::Default;
        result = QVariant(static_cast<int>(dictionaryType));
        break;
    }
    case QVirtualKeyboardSelectionListModel::Role::CanRemoveSuggestion:
        result = QVariant(d->dlmHasWord(d->wordCandidates.at(index).symbs));
        break;
    default:
        result = QVirtualKeyboardAbstractInputMethod::selectionListData(type, index, role);
        break;
    }
    return result;
}

void T9WriteInputMethod::selectionListItemSelected(QVirtualKeyboardSelectionListModel::Type type, int index)
{
    Q_UNUSED(type);
    Q_D(T9WriteInputMethod);

#ifdef HAVE_XT9
    switch (d->engineMode) {
    case T9WriteInputMethod::EngineMode::SimplifiedChinese:
        if (inputEngine()->inputMode() != QVirtualKeyboardInputEngine::InputMode::ChineseHandwriting)
            break;

    [[fallthrough]]; case T9WriteInputMethod::EngineMode::Japanese:
        if (d->wordCandidates[index].origin == T9WriteWordCandidate::Origin::T9Write) {
            if (d->xt9AllSymbsArePinyin(d->wordCandidates[index].symbs)) {
                int indexOfFirstXt9Candidate;
                for (indexOfFirstXt9Candidate = 0; indexOfFirstXt9Candidate < d->wordCandidates.size(); ++indexOfFirstXt9Candidate) {
                    if (d->wordCandidates[indexOfFirstXt9Candidate].origin == T9WriteWordCandidate::Origin::XT9)
                        break;
                }

                while (indexOfFirstXt9Candidate < d->wordCandidates.size()) {
                    d->wordCandidates.removeAt(indexOfFirstXt9Candidate);
                }

                int xt9DefaultListIndex = 0;
                d->appendWordCandidates(d->wordCandidates, d->activeWordIndex, d->wordCandidates[index].symbs, d->xt9BuildSelectionList(d->wordCandidates[index].symbs, &xt9DefaultListIndex), xt9DefaultListIndex, T9WriteWordCandidate::Origin::XT9);
                d->activeWordIndex = index;

                emit selectionListChanged(QVirtualKeyboardSelectionListModel::Type::WordCandidateList);
                emit selectionListActiveItemChanged(QVirtualKeyboardSelectionListModel::Type::WordCandidateList, d->activeWordIndex);
                return;
            }
        }
        break;

    default:
        break;
    }
#endif

    d->select(index);
}

bool T9WriteInputMethod::selectionListRemoveItem(QVirtualKeyboardSelectionListModel::Type type, int index)
{
    Q_UNUSED(type)
    Q_D(T9WriteInputMethod);
    if (index < 0 || index >= d->wordCandidates.size())
        return false;
    d->dlmRemoveWord(d->wordCandidates.at(index).symbs);
    if (d->wordCandidates.size() > 1) {
        d->wordCandidates.removeAt(index);
        emit selectionListChanged(QVirtualKeyboardSelectionListModel::Type::WordCandidateList);
        emit selectionListActiveItemChanged(QVirtualKeyboardSelectionListModel::Type::WordCandidateList, d->activeWordIndex);
    } else {
        inputContext()->clear();
        reset();
    }
    return true;
}

QList<QVirtualKeyboardInputEngine::PatternRecognitionMode> T9WriteInputMethod::patternRecognitionModes() const
{
    return QList<QVirtualKeyboardInputEngine::PatternRecognitionMode>()
            << QVirtualKeyboardInputEngine::PatternRecognitionMode::Handwriting;
}

QVirtualKeyboardTrace *T9WriteInputMethod::traceBegin(
        int traceId, QVirtualKeyboardInputEngine::PatternRecognitionMode patternRecognitionMode,
        const QVariantMap &traceCaptureDeviceInfo, const QVariantMap &traceScreenInfo)
{
    Q_D(T9WriteInputMethod);
    return d->traceBegin(traceId, patternRecognitionMode, traceCaptureDeviceInfo, traceScreenInfo);
}

bool T9WriteInputMethod::traceEnd(QVirtualKeyboardTrace *trace)
{
    Q_D(T9WriteInputMethod);
    d->traceEnd(trace);
    return true;
}

bool T9WriteInputMethod::reselect(int cursorPosition, const QVirtualKeyboardInputEngine::ReselectFlags &reselectFlags)
{
    Q_D(T9WriteInputMethod);

    if (d->sessionSettings.recognitionMode == scrMode)
        return false;

    QVirtualKeyboardInputContext *ic = inputContext();
    if (!ic)
        return false;

    const QVirtualKeyboardInputEngine::InputMode inputMode = inputEngine()->inputMode();
    const int maxLength = (inputMode == QVirtualKeyboardInputEngine::InputMode::ChineseHandwriting ||
            inputMode == QVirtualKeyboardInputEngine::InputMode::JapaneseHandwriting ||
            inputMode == QVirtualKeyboardInputEngine::InputMode::KoreanHandwriting) ? 16 : 32;
    const QString surroundingText = ic->surroundingText();
    int replaceFrom = 0;

    if (cursorPosition > surroundingText.length())
        return false;

    if (reselectFlags.testFlag(QVirtualKeyboardInputEngine::ReselectFlag::WordBeforeCursor)) {
        for (int i = cursorPosition - 1; i >= 0 && d->stringStart.length() < maxLength; --i) {
            QChar c = surroundingText.at(i);
            if (!d->isValidInputChar(c))
                break;
            d->stringStart.insert(0, c);
            --replaceFrom;
        }

        while (replaceFrom < 0 && d->isJoiner(d->stringStart.at(0))) {
            d->stringStart.remove(0, 1);
            ++replaceFrom;
        }
    }

    if (reselectFlags.testFlag(QVirtualKeyboardInputEngine::ReselectFlag::WordAtCursor) && replaceFrom == 0) {
        d->stringStart.clear();
        return false;
    }

    if (reselectFlags.testFlag(QVirtualKeyboardInputEngine::ReselectFlag::WordAfterCursor)) {
        for (int i = cursorPosition; i < surroundingText.length() && d->stringStart.length() < maxLength; ++i) {
            QChar c = surroundingText.at(i);
            if (!d->isValidInputChar(c))
                break;
            d->stringStart.append(c);
        }

        while (replaceFrom > -d->stringStart.length()) {
            int lastPos = d->stringStart.length() - 1;
            if (!d->isJoiner(d->stringStart.at(lastPos)))
                break;
            d->stringStart.remove(lastPos, 1);
        }
    }

    if (d->stringStart.isEmpty())
        return false;

    if (reselectFlags.testFlag(QVirtualKeyboardInputEngine::ReselectFlag::WordAtCursor) && replaceFrom == -d->stringStart.length() && d->stringStart.length() < maxLength) {
        d->stringStart.clear();
        return false;
    }

    if (d->isJoiner(d->stringStart.at(0))) {
        d->stringStart.clear();
        return false;
    }

    if (d->isJoiner(d->stringStart.at(d->stringStart.length() - 1))) {
        d->stringStart.clear();
        return false;
    }

    ic->setPreeditText(d->stringStart, QList<QInputMethodEvent::Attribute>(), replaceFrom, d->stringStart.length());
    for (int i = 0; i < d->stringStart.length(); ++i)
        d->caseFormatter.ensureLength(i + 1, d->stringStart.at(i).isUpper() ? QVirtualKeyboardInputEngine::TextCase::Upper : QVirtualKeyboardInputEngine::TextCase::Lower);
    int xt9DefaultListIndex = 0;
    d->activeWordIndex = 0;
    d->appendWordCandidates(d->wordCandidates, d->activeWordIndex, d->stringStart, d->xt9BuildSelectionList(d->stringStart, &xt9DefaultListIndex), xt9DefaultListIndex, T9WriteWordCandidate::Origin::XT9);
    emit selectionListChanged(QVirtualKeyboardSelectionListModel::Type::WordCandidateList);
    emit selectionListActiveItemChanged(QVirtualKeyboardSelectionListModel::Type::WordCandidateList, d->activeWordIndex);

    return true;
}

void T9WriteInputMethod::timerEvent(QTimerEvent *timerEvent)
{
    Q_D(T9WriteInputMethod);
    int timerId = timerEvent->timerId();
    qCDebug(lcT9Write) << "T9WriteInputMethod::timerEvent():" << timerId;
    if (timerId == d->resultTimer) {
        d->stopResultTimer();

        // Ignore if the result is not yet available
        if (d->resultId != d->lastResultId) {
            qCDebug(lcT9Write) << "T9WriteInputMethod::timerEvent(): Result not yet available";
            return;
        }

        if (d->sessionSettings.recognitionMode != scrMode) {
#ifndef QT_VIRTUALKEYBOARD_RECORD_TRACE_INPUT
            // Don't clear traces in UCR mode if dictionary is loaded.
            // In UCR mode the whole purpose is to write the word with
            // one or few strokes.
            if (d->sessionSettings.recognitionMode == ucrMode) {
                const std::lock_guard<QRecursiveMutex> dictionaryGuard(d->dictionaryLock);
                if (d->attachedDictionary)
                    return;
            }

            const QVirtualKeyboardInputEngine::InputMode inputMode = inputEngine()->inputMode();
            if (inputMode != QVirtualKeyboardInputEngine::InputMode::ChineseHandwriting &&
                    inputMode != QVirtualKeyboardInputEngine::InputMode::JapaneseHandwriting &&
                    inputMode != QVirtualKeyboardInputEngine::InputMode::KoreanHandwriting) {
                d->clearTraces();
            }
#endif
        } else {
            d->select();
        }
    }
}

} // namespace QtVirtualKeyboard
QT_END_NAMESPACE
