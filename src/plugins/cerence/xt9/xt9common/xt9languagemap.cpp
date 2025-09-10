// Copyright (C) 2021 The Qt Company Ltd.
// SPDX-License-Identifier: LicenseRef-Qt-Commercial OR GPL-3.0-only

#include "xt9languagemap.h"

QT_BEGIN_NAMESPACE
namespace QtVirtualKeyboard {

const Xt9LanguageMap::SimpleLanguageMapEntry Xt9LanguageMap::SIMPLE_LANGUAGE_MAP[] = {
    { ET9PLIDAbkhazian,           QLocale::Language::Abkhazian },
    { ET9PLIDAfar,                QLocale::Language::Afar },
    { ET9PLIDAfrikaans,           QLocale::Language::Afrikaans },
    { ET9PLIDAlbanian,            QLocale::Language::Albanian },
    { ET9PLIDAmharic,             QLocale::Language::Amharic },
    { ET9PLIDArabic,              QLocale::Language::Arabic },
    { ET9PLIDArmenian,            QLocale::Language::Armenian },
    { ET9PLIDAssamese,            QLocale::Language::Assamese },
    { ET9PLIDAymara,              QLocale::Language::Aymara },
    { ET9PLIDAzerbaijani,         QLocale::Language::Azerbaijani },
    { ET9PLIDBashkir,             QLocale::Language::Bashkir },
    { ET9PLIDBasque,              QLocale::Language::Basque },
    { ET9PLIDBelarusian,          QLocale::Language::Belarusian },
    { ET9PLIDBengali,             QLocale::Language::Bengali },
    { ET9PLIDBislama,             QLocale::Language::Bislama },
    { ET9PLIDBosnian,             QLocale::Language::Bosnian },
    { ET9PLIDBreton,              QLocale::Language::Breton },
    { ET9PLIDBulgarian,           QLocale::Language::Bulgarian },
    { ET9PLIDBurmese,             QLocale::Language::Burmese },
    { ET9PLIDCatalan,             QLocale::Language::Catalan },
    { ET9PLIDChineseSimplified,   QLocale::Language::Chinese },
    { ET9PLIDCorsican,            QLocale::Language::Corsican },
    { ET9PLIDCroatian,            QLocale::Language::Croatian },
    { ET9PLIDCzech,               QLocale::Language::Czech },
    { ET9PLIDDanish,              QLocale::Language::Danish },
    { ET9PLIDDutch,               QLocale::Language::Dutch },
    { ET9PLIDEnglish,             QLocale::Language::English },
    { ET9PLIDEsperanto,           QLocale::Language::Esperanto },
    { ET9PLIDEstonian,            QLocale::Language::Estonian },
    { ET9PLIDFilipino,            QLocale::Language::Filipino },
    { ET9PLIDFinnish,             QLocale::Language::Finnish },
    { ET9PLIDFrench,              QLocale::Language::French },
    { ET9PLIDGalician,            QLocale::Language::Galician },
    { ET9PLIDGeorgian,            QLocale::Language::Georgian },
    { ET9PLIDGerman,              QLocale::Language::German },
    { ET9PLIDGerman,              QLocale::Language::LowGerman },
    { ET9PLIDGerman,              QLocale::Language::SwissGerman },
    { ET9PLIDGreek,               QLocale::Language::Greek },
    { ET9PLIDGreenlandic,         QLocale::Language::Greenlandic },
    { ET9PLIDGuarani,             QLocale::Language::Guarani },
    { ET9PLIDGujarati,            QLocale::Language::Gujarati },
    { ET9PLIDHausa,               QLocale::Language::Hausa },
    { ET9PLIDHawaiian,            QLocale::Language::Hawaiian },
    { ET9PLIDHebrew,              QLocale::Language::Hebrew },
    { ET9PLIDHindi,               QLocale::Language::Hindi },
    { ET9PLIDHungarian,           QLocale::Language::Hungarian },
    { ET9PLIDIcelandic,           QLocale::Language::Icelandic },
    { ET9PLIDIgbo,                QLocale::Language::Igbo },
    { ET9PLIDIndonesian,          QLocale::Language::Indonesian },
    { ET9PLIDInterlingua,         QLocale::Language::Interlingua },
    { ET9PLIDInterlingue,         QLocale::Language::Interlingue },
    { ET9PLIDInuktitut,           QLocale::Language::Inuktitut },
    { ET9PLIDInupiak,             QLocale::Language::Inupiak },
    { ET9PLIDIrish,               QLocale::Language::Irish },
    { ET9PLIDItalian,             QLocale::Language::Italian },
    { ET9PLIDJapanese,            QLocale::Language::Japanese },
    { ET9PLIDJavanese,            QLocale::Language::Javanese },
    { ET9PLIDKannada,             QLocale::Language::Kannada },
    { ET9PLIDKashmiri,            QLocale::Language::Kashmiri },
    { ET9PLIDKazakh,              QLocale::Language::Kazakh },
    { ET9PLIDKhmer,               QLocale::Language::Khmer },
    { ET9PLIDKirghiz,             QLocale::Language::Kirghiz },
    { ET9PLIDKonkani,             QLocale::Language::Konkani },
    { ET9PLIDKorean,              QLocale::Language::Korean },
    { ET9PLIDKurdish,             QLocale::Language::Kurdish },
    { ET9PLIDLao,                 QLocale::Language::Lao },
    { ET9PLIDLatin,               QLocale::Language::Latin },
    { ET9PLIDLatvian,             QLocale::Language::Latvian },
    { ET9PLIDLingala,             QLocale::Language::Lingala },
    { ET9PLIDLithuanian,          QLocale::Language::Lithuanian },
    { ET9PLIDMacedonian,          QLocale::Language::Macedonian },
    { ET9PLIDMalagasy,            QLocale::Language::Malagasy },
    { ET9PLIDMalay,               QLocale::Language::Malay },
    { ET9PLIDMalayalam,           QLocale::Language::Malayalam },
    { ET9PLIDMaltese,             QLocale::Language::Maltese },
    { ET9PLIDMaori,               QLocale::Language::Maori },
    { ET9PLIDMarathi,             QLocale::Language::Marathi },
    { ET9PLIDMongolian,           QLocale::Language::Mongolian },
    { ET9PLIDNepali,              QLocale::Language::Nepali },
    { ET9PLIDNorwegian,           QLocale::Language::NorwegianBokmal },
    { ET9PLIDNorwegian,           QLocale::Language::NorwegianNynorsk },
    { ET9PLIDOccitan,             QLocale::Language::Occitan },
    { ET9PLIDOriya,               QLocale::Language::Oriya },
    { ET9PLIDOromo,               QLocale::Language::Oromo },
    { ET9PLIDPashto,              QLocale::Language::Pashto },
    { ET9PLIDPersian,             QLocale::Language::Persian },
    { ET9PLIDPolish,              QLocale::Language::Polish },
    { ET9PLIDPortuguese,          QLocale::Language::Portuguese },
    { ET9PLIDPunjabi,             QLocale::Language::Punjabi },
    { ET9PLIDQuechua,             QLocale::Language::Quechua },
    { ET9PLIDRomanian,            QLocale::Language::Romanian },
    { ET9PLIDRussian,             QLocale::Language::Russian },
    { ET9PLIDSami,                QLocale::Language::NorthernSami },
    { ET9PLIDSamoan,              QLocale::Language::Samoan },
    { ET9PLIDSangho,              QLocale::Language::Sango },
    { ET9PLIDSanskrit,            QLocale::Language::Sanskrit },
    { ET9PLIDSerbian,             QLocale::Language::Serbian },
    { ET9PLIDSesotho,             QLocale::Language::NorthernSotho },
    { ET9PLIDSesotho,             QLocale::Language::SouthernSotho },
    { ET9PLIDShona,               QLocale::Language::Shona },
    { ET9PLIDSindhi,              QLocale::Language::Sindhi },
    { ET9PLIDSinhala,             QLocale::Language::Sinhala },
    { ET9PLIDSiswati,             QLocale::Language::Swati },
    { ET9PLIDSlovak,              QLocale::Language::Slovak },
    { ET9PLIDSlovenian,           QLocale::Language::Slovenian },
    { ET9PLIDSomali,              QLocale::Language::Somali },
    { ET9PLIDSpanish,             QLocale::Language::Spanish },
    { ET9PLIDSundanese,           QLocale::Language::Sundanese },
    { ET9PLIDSwahili,             QLocale::Language::Swahili },
    { ET9PLIDSwedish,             QLocale::Language::Swedish },
    { ET9PLIDTajik,               QLocale::Language::Tajik },
    { ET9PLIDTamil,               QLocale::Language::Tamil },
    { ET9PLIDTatar,               QLocale::Language::Tatar },
    { ET9PLIDTelugu,              QLocale::Language::Telugu },
    { ET9PLIDThai,                QLocale::Language::Thai },
    { ET9PLIDTibetan,             QLocale::Language::Tibetan },
    { ET9PLIDTigrinya,            QLocale::Language::Tigrinya },
    { ET9PLIDTonga,               QLocale::Language::Tongan },
    { ET9PLIDTsonga,              QLocale::Language::Tsonga },
    { ET9PLIDTswana,              QLocale::Language::Tswana },
    { ET9PLIDTurkish,             QLocale::Language::Turkish },
    { ET9PLIDTurkmen,             QLocale::Language::Turkmen },
    { ET9PLIDUkrainian,           QLocale::Language::Ukrainian },
    { ET9PLIDUrdu,                QLocale::Language::Urdu },
    { ET9PLIDUzbek,               QLocale::Language::Uzbek },
    { ET9PLIDVenda,               QLocale::Language::Venda },
    { ET9PLIDVietnamese,          QLocale::Language::Vietnamese },
    { ET9PLIDVolapuk,             QLocale::Language::Volapuk },
    { ET9PLIDWelsh,               QLocale::Language::Welsh },
    { ET9PLIDWolof,               QLocale::Language::Wolof },
    { ET9PLIDXhosa,               QLocale::Language::Xhosa },
    { ET9PLIDYiddish,             QLocale::Language::Yiddish },
    { ET9PLIDYoruba,              QLocale::Language::Yoruba },
    { ET9PLIDZhuang,              QLocale::Language::Zhuang },
    { ET9PLIDZulu,                QLocale::Language::Zulu },
    // End-of-map
    { ET9PLIDNone,                QLocale::Language::AnyLanguage }
};

const struct Xt9LanguageMap::LanguageMapEntry Xt9LanguageMap::LANGUAGE_MAP[] = {
    { ET9LIDEnglish_UK,                 QLocale(QLocale::English, QLocale::UnitedKingdom) },
    { ET9LIDEnglish_Australia,          QLocale(QLocale::English, QLocale::Australia) },
    { ET9LIDEnglish_India,              QLocale(QLocale::English, QLocale::India) },
    { ET9LIDEnglish_US,                 QLocale(QLocale::English, QLocale::UnitedStates) },
    { ET9PLIDEnglish|ET9SLIDDEFAULT,    QLocale(QLocale::English, QLocale::UnitedKingdom) },
    { ET9LIDSpanish_LatinAmerican,      QLocale(QLocale::Spanish, QLocale::LatinAmerica) },
    { ET9PLIDSpanish|ET9SLIDDEFAULT,    QLocale(QLocale::Spanish, QLocale::Spain) },
    { ET9LIDFrench_Canada,              QLocale(QLocale::French, QLocale::Canada) },
    { ET9LIDFrench_Switzerland,         QLocale(QLocale::French, QLocale::Switzerland) },
    { ET9PLIDFrench|ET9SLIDDEFAULT,     QLocale(QLocale::French, QLocale::France) },
    { ET9LIDItalian_Switzerland,        QLocale(QLocale::Italian, QLocale::Switzerland) },
    { ET9LIDDutch_Belgium,              QLocale(QLocale::Dutch, QLocale::Belgium) },
    { ET9PLIDPortuguese|ET9SLIDDEFAULT, QLocale(QLocale::Portuguese, QLocale::Portugal) },
    { ET9LIDPortuguese_Brazil,          QLocale(QLocale::Portuguese, QLocale::Brazil) },
    { ET9PLIDChineseSimplified,         QLocale(QLocale::Chinese, QLocale::SimplifiedHanScript, QLocale::China) },
    { ET9PLIDChineseTraditional,        QLocale(QLocale::Chinese, QLocale::TraditionalHanScript, QLocale::Taiwan) },
    { ET9PLIDChineseHongkong,           QLocale(QLocale::Chinese, QLocale::TraditionalHanScript, QLocale::HongKong) },
    { ET9PLIDChineseSingapore,          QLocale(QLocale::Chinese, QLocale::TraditionalHanScript, QLocale::Singapore) },
    { ET9LIDJapanese_Hiragana,          QLocale(QLocale::Japanese) },
    // End-of-map
    { 0,                                QLocale(QLocale::AnyLanguage) },
};

ET9U32 Xt9LanguageMap::languageId(const QLocale &locale)
{
    const QLocale::Language localeLanguage = locale.language();
    const QLocale::Territory localeTerritory = locale.territory();

    for (int i = 0; LANGUAGE_MAP[i].languageId != 0; ++i) {
        const QLocale &item = LANGUAGE_MAP[i].locale;
        if (item.language() == localeLanguage && item.territory() == localeTerritory)
            return LANGUAGE_MAP[i].languageId;
    }

    const SimpleLanguageMapEntry *simpleLanguageMapIterator = SIMPLE_LANGUAGE_MAP;
    for (; simpleLanguageMapIterator->localeLanguage != QLocale::Language::AnyLanguage;
         simpleLanguageMapIterator++) {
        if (simpleLanguageMapIterator->localeLanguage == localeLanguage)
            return simpleLanguageMapIterator->languageId;
    }

    return ET9PLIDNone;
}

QLocale Xt9LanguageMap::locale(ET9U32 languageId)
{
    for (int i = 0; LANGUAGE_MAP[i].languageId != 0; ++i) {
        if (LANGUAGE_MAP[i].languageId == languageId)
            return LANGUAGE_MAP[i].locale;
    }

    if (!(languageId & ET9SLIDMASK) &&
            (languageId < ET9PLIDChineseTraditional || languageId > ET9PLIDChineseSingapore)) {

        languageId |= ET9SLIDDEFAULT;

        for (int i = 0; LANGUAGE_MAP[i].languageId != 0; ++i) {
            if (LANGUAGE_MAP[i].languageId == languageId)
                return LANGUAGE_MAP[i].locale;
        }
    }

    const ET9U32 plid = languageId & ET9PLIDMASK;
    const SimpleLanguageMapEntry *simpleLanguageMapIterator = SIMPLE_LANGUAGE_MAP;
    for (; simpleLanguageMapIterator->localeLanguage != QLocale::Language::AnyLanguage;
         simpleLanguageMapIterator++) {
        if (simpleLanguageMapIterator->languageId == plid)
            return QLocale(simpleLanguageMapIterator->localeLanguage);
    }

    return QLocale(QLocale::AnyLanguage);
}

} // namespace QtVirtualKeyboard
QT_END_NAMESPACE
