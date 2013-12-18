# QtVKB - Qt Virtual Keyboard

QtVKB is a virtual keyboard framework that consists of C++ backend
supporting custom input methods as well as UI frontend implemented in QML.

The project is split into following subprojects:
- *demo.pro* QtVKB Demo application
- *qtvkb.pro* QtVKB C++ backend for input engine and QPlatformInputContext integration
- *styles.pro* QtVKB Style plugin that enables style decorations for keyboard

The input methods are implemented either in C++ or QML languages.
The QtVKB provides an example implementations of PlainInputMethod, MultitapInputMethod
and HunspellInputMethod. The MultitapInputMethod is implemented in QML while
the others are implemented in C++.

For more details, please refer to the documentation in qtvkb/doc/html directory.

## Build instructions

The QtVKB can be built for Linux Desktop/X11 or Boot2Qt targets. The target is
automatically detected by QMAKE and requires no special configuration parameters.

QtCreator is preferred build environment for QtVKB as you can then leverage from
shadow build and rapidly switch between build targets.

### Configuration options

- *CONFIG+=disable-xcb* Disables X11 integration
- *CONFIG+=disable-hunspell* Disables Hunspell integration
- *CONFIG+=retro-style* Enables Retro style

### Extra targets

- *docs* Generates documentation

### Hunspell integration

By default, HunspellInputMethod will not be available unless the Hunspell library and
development headers are found. For Linux/X11 target the Hunspell library can be provided
by installing libhunspell-dev package. Alternatively the Hunspell sources can be extracted into
qtvkb/hunspell directory. If Hunspell sources are used, then the dictionary
files must also be copied into qtvkb/hunspell/data directory. Furthermore,
if Hunspell sources are used, the hunspell.pro will be used for all targets.

## Deployment instructions

### Linux/X11

Add Deploy Step that executes "make install" command, then deploy using *Deploy All* command.

### Boot2Qt

Remount target file system as read-write before deployment.

    adb -s <deviceid> remount

Deploy using *Deploy All* command.
