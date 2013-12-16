OTHER_FILES += \
            $$PWD/qtvkb.qdocconf \
            $$PWD/src/index.qdoc \
            $$PWD/src/deployment_guide.qdoc \
            $$PWD/src/technical_guide.qdoc \
            $$PWD/src/examples/CustomInputMethod.qml

docs_target.target = docs
docs_target.commands = $$[QT_HOST_BINS]/qdoc $$PWD/qtvkb.qdocconf

QMAKE_EXTRA_TARGETS = docs_target
