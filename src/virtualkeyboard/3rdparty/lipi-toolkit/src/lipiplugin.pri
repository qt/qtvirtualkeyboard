include(lipicommon.pri)

CONFIG -= static
CONFIG += plugin

DESTDIR = $$MODULE_BASE_OUTDIR/plugins/lipi_toolkit

### This is a bad install location for arch-specific binaries.
target.path = $$[QT_INSTALL_DATA]/qtvirtualkeyboard/lipi_toolkit/lib
INSTALLS += target
