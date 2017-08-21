TARGET = qtt9write_db

CONFIG += static

T9WRITE_RESOURCE_FILES = \
    $$files(data/arabic/*.bin) \
    $$files(data/hebrew/*.bin) \
    $$files(data/*.bin) \
    $$files(data/*.ldb) \
    $$files(data/*.hdb) \
    $$files(data/*.phd)

# Note: Compression is disabled, because the resource is accessed directly from the memory
QMAKE_RESOURCE_FLAGS += -no-compress
CONFIG += resources_big

include(../../generateresource.pri)

RESOURCES += $$generate_resource(t9write_db.qrc, $$T9WRITE_RESOURCE_FILES, /QtQuick/VirtualKeyboard/T9Write)

load(qt_helper_lib)

# Needed for resources
CONFIG += qt
QT = core
