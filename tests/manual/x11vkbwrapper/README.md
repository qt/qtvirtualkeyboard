# Qt virtual keyboard wrapper for X11

This application is a Qt virtual keyboard wrapper that uses Qt virtual
keyboard for any X11 input. Application uses At-Spi2 library for
listening focus-in events on text widgets and pops up the Qt virtual
keyboard when an accepted focus-in event is received. There's also
support for listening focus-in events from Chromium browser. For
mapping and sending the key events to focused text widget the application
uses libXtst, libX11 and libxdo which are also
external dependencies to the application among At-Spi2 library.

## Libraries to be installed
libatspi2.0-dev libxdo-dev libxtst-dev

## Running the x11vkbwrapper
1. Build the x11vkbwrapper project.
2. For x11vkbwrapper application to be able to send key events to X11 clients and to enable the SHIFT - key the run environment for x11vkbwrapper application has to have environment variable QT_VIRTUALKEYBOARD_FORCE_EVENTS_WITHOUT_FOCUS set.
 It can be empty but it has to be set. Setting the environment variable enables usage of the virtual keyboard input method without a focused Qt specific input object.
3. If Firefox is to be used the environment variable GNOME_ACCESSIBILITY has to be set to 1 to enable the At-Spi support.
4. Run the x11vkbwrapper.

## Enable Chrome/Chromium support
1. Build the vkbnativehost project.
2. From vkbnativehost folder run shell script install_host.sh with following parameters: "chromium" "/full/path/to/vkbnativehost_executable". Exclude the filename from the path.
    1. For chrome browser replace the "chromium" parameter with "chrome".
    2. The script updates the path to vkbnativehost executable in x11vkb.host.json file and copies that .json file into the current user local space $HOME/.config/chromium/NativeMessagingHosts.
    3. If sudo is used .json file will be copied in chromium global space /etc/chromium-browser/native-messaging-hosts.
3. In Chromium/Chrome browser go to url chrome://extensions/.
4. Enable Developer Mode by clicking the toggle switch next to Developer mode.
5. Click the "Load unpacked" button and provide there the chromeextension folder.
6. x11vkbwrapper must be running before the browser is started to have the show/hide keyboard support enabled.

## Setting up and running the x11vkbtest test application
### Background
Test application (x11vkbtest) will start the x11vkbwrapper and uses Linux proc filesystem for obtaining memory consumption information and libXtst, libX11 and libxdo libraries for generating and sending key events.
There are three different tests that can be run:
1. Testing the start/close cycle of the x11vkbwrapper application is run in 50ms intervals and the current free system memory is recorded at the beginning and at the end of the test. By default amount of 50 start/close cycles will be run.
2. Key event test opens up gedit text editor and sends key events to the x11vkbwrapper app in 50ms interval writing by default a 100 character string or a string as long as user has defined to gedit and verifies the results by comparing the written text to the predefined one.
3. Language change test sends key events to the x11vkbwrapper app in 120ms interval making the language change to take place. Result is verified against information on input context locale's native language name read from a .json file produced by the app under test (x11vkbwrapper). By default amount of 10 language change events will be performed.

Test results are produced in a form of csv file and an png image of the memory consumption chart in a folder where this application is run. Test report includes the duration of each test, memory consumption information on the system and the process being tested and the overall duration of all tests that has been run.

### Steps to build and run x11vkbtest
1. Build the x11vkbtest project.
2. Uncomment 'DEFINES += QT_TESTING_RUN' from x11vkbwrapper.pro and build/re-build it preferably in RELEASE mode.
    1. The above given DEFINES+=QT_TESTING_RUN enables x11vkbwrapper app to write the current selected language in qtvirtualkeyboard into a .json file in /home/<username</x11vkbwrapper_language/currentLang.json which will be used by x11vkbtest to obtain the current selected language when testing the language change events.
3. To be able to start running the tests command line argument --exec <absolute_path_to_x11vkbwrapper_executable> needs to be given when starting the x11vkbtest app and environment variable QT_VIRTUALKEYBOARD_FORCE_EVENTS_WITHOUT_FOCUS needs to be set.
4. The three tests that can be run as a series or separately:
    1. Start & close the x11vkbwrapper application
        1. command line argument --sc <number_of_times>
    2. Key events
        1. command line argument --ko <number_of_keyevents>
    3. Language change events
        1. command line argument --lc <number_of_language_changes>
5. If no command line arguments are specified all of the tests are run in the order specified above using default values.
6. If parameters --sc, --ko and/or --lc are used the corresponding value(s) has/have to be given explicitly.
7. Example command line arguments: --exec <absolute_path_to_x11vkbwrapper> --sc 100 --lc 100

The --sc test doesn't produce any visible results in the chart and it will run approximately few seconds when no parameter --sc with a value specifying the start/close cycles has been given. If --sc <number_of_times> has been given then bigger the number the longer the time is that nothing is visually happening during the --sc test, only a static chart is visible. During --ko and --lc tests live memory consumption is drawn to the chart.
No interaction, mouse or keyboard etc., should be performed during the test run. It will cause libx11 pointer coordinate getting- and libxtst button event sending functions to go haywire
and thus x11vkbtest will fail to click on correct points on the x11vkbwrapper keyboard.
