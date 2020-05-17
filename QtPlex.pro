include(third_party/QHotkey/qhotkey.pri)

TEMPLATE = app

QT += qml quick
QT += webengine
QT += webenginewidgets
QT += core
QT += gui x11extras

CONFIG += c++11

SOURCES += src/app/applicationwindow.cpp \
    src/app/configserverhelp.cpp \
    src/app/javascript_loader.cpp \
    src/app/key_events.cpp \
    src/app/main.cpp \
    src/app/media_status_notification.cc \
    src/app/plex_web_page.cpp \
    src/app/settingsdialog.cpp

# Additional import path used to resolve QML modules in Qt Creator's code model
QML_IMPORT_PATH =

# Additional import path used to resolve QML modules just for Qt Quick Designer
QML_DESIGNER_IMPORT_PATH =

# The following define makes your compiler emit warnings if you use
# any feature of Qt which as been marked deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

HEADERS += \
    include/javascript_loader.h \
    include/key_events.h \
    include/media_status_notification.h \
    include/plex_web_page.h \
    include/webdisplay.h \
    include/constants.h \
    include/applicationwindow.h \
    include/configserverhelp.h \
    include/settingsdialog.h

unix|win32: LIBS += -lX11

# Add the JavaScript source files and Resources to build output
# Explanation of the following can be found here:
# https://dragly.org/2013/11/05/copying-data-files-to-the-build-directory-when-working-with-qmake/
include_extras.commands = $(COPY_DIR) $$PWD/src/js $$OUT_PWD && $(COPY_DIR) $$PWD/res $$OUT_PWD

first.depends = $(first) include_extras
export(first.depends)
export(include_extras.commands)
QMAKE_EXTRA_TARGETS += first include_extras

RESOURCES += \
    resources.qrc
