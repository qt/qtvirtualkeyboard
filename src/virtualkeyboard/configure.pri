VKB_SOURCE_TREE = $$PWD
VALID_LANGUAGES = \
    ar_AR \
    bg_BG \
    cs_CZ \
    da_DK \
    de_DE \
    el_GR \
    en_GB \
    en_US \
    es_ES \
    es_MX \
    et_EE \
    fa_FA \
    fi_FI \
    fr_CA \
    fr_FR \
    he_IL \
    hi_IN \
    hr_HR \
    hu_HU \
    id_ID \
    it_IT \
    ja_JP \
    ko_KR \
    ms_MY \
    nb_NO \
    nl_NL \
    pl_PL \
    pt_BR \
    pt_PT \
    ro_RO \
    ru_RU \
    sk_SK \
    sl_SI \
    sq_AL \
    sr_SP \
    sv_SE \
    th_TH \
    tr_TR \
    uk_UA \
    vi_VN \
    zh_CN \
    zh_TW

defineReplace(qtConfGetLanguageList) {
    val = $${2}
    isEmpty(val): val = $$qtConfGetNextCommandlineArg()
    contains(val, "^-.*|[A-Z_]+=.*")|isEmpty(val) {
        qtConfAddError("No value supplied to command line option '$$1'.")
        return()
    }
    vals = $$split(val, ',')
    for (l, vals) {
        languages += $$l
        equals(val, "all"): \
            return($$VALID_LANGUAGES)

        !contains(VALID_LANGUAGES, $$l) {
            qtConfAddError("Language '$$l' is not supported by the Qt Virtual Keyboard." \
                           "The list of valid languages is:" \
                           "$$VALID_LANGUAGES");
            return()
        }
    }
    return($$languages)
}

defineTest(qtConfCommandline_enableLang) {
    languages = $$qtConfGetLanguageList($$1, $$2)

    # explicitly disable all languages that are currently not explicitly set
    for (l, VALID_LANGUAGES) {
        isEmpty(config.input.lang-$${l}) {
            config.input.lang-$${l} = "no"
            export(config.input.lang-$${l})
        }
    }

    for (l, languages) {
        config.input.lang-$${l} = "yes"
        export(config.input.lang-$${l})
    }
}

defineTest(qtConfCommandline_disableLang) {
    languages = $$qtConfGetLanguageList($$1, $$2)

    for (l, languages) {
        config.input.lang-$${l} = "no"
        export(config.input.lang-$${l})
    }
}


# T9Write tests

T9WRITE_BASE_DIR = $$VKB_SOURCE_TREE/3rdparty/t9write

defineTest(t9writeFindSharedLibrary) {
    contains(QT_ARCH, arm) {
        LIB_DIR = $$BASE_DIR/lib/arm/shared
    } else: linux {
        LIB_DIR = $$BASE_DIR/lib/linux-x86/shared
    } else: win32 {
        LIB_DIR = $$BASE_DIR/lib/win32/shared
    } else {
        return(false)
    }
    win32 {
        result = $$files($$LIB_DIR/$$1/*.obj)
        isEmpty(result): result = $$files($$LIB_DIR/$$1/*.lib)
        isEmpty(result) {
            return(false)
        }
    } else {
        result = $$files($$LIB_DIR/$$1/*.o)
        isEmpty(result): result = $$files($$LIB_DIR/$$1/*.so)
        isEmpty(result) {
            return(false)
        }
    }
    return(true)
}

defineTest(t9writeFindStaticLibrary) {
    contains(QT_ARCH, arm) {
        LIB_DIR = $$BASE_DIR/lib/arm/shared
    } else: linux {
        LIB_DIR = $$BASE_DIR/lib/linux-x86/shared
    } else: win32 {
        LIB_DIR = $$BASE_DIR/lib/win32/shared
    } else {
        return(false)
    }
    win32 {
        result = $$files($$LIB_DIR/$$1/*.obj)
        isEmpty(result): result = $$files($$LIB_DIR/$$1/*.lib)
        isEmpty(result) {
            return(false)
        }
    } else {
        result = $$files($$LIB_DIR/$$1/*.o)
        isEmpty(result): result = $$files($$LIB_DIR/$$1/*.a)
        isEmpty(result) {
            return(false)
        }
    }
    return(true)
}

defineTest(qtConfTest_t9write-alphabetic) {
    !exists($${T9WRITE_BASE_DIR}/api/decuma_hwr.h) {
        return (false)
    }
    !t9writeFindStaticLibrary(alphabetic)|!t9writeFindSharedLibrary(alphabetic) {
        return (false)
    }
    return(true)
}

defineTest(qtConfTest_t9write-cjk) {
    !exists($${T9WRITE_BASE_DIR}/api/decuma_hwr_cjk.h) {
        return (false)
    }
    !t9writeFindStaticLibrary(cjk)|!t9writeFindSharedLibrary(cjk) {
        return (false)
    }
    return(true)
}


# 3rdpary hunspell support

defineTest(qtConfTest_3rdpartyHunspell) {
    !exists($$VKB_SOURCE_TREE/src/plugins/hunspell/3rdparty/hunspell/hunspell.h): \
        return(false)
    !exists($$VKB_SOURCE_TREE/src/plugins/hunspell/3rdparty/hunspell/data): \
        return(false)
    return(true)
}
