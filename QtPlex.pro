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
    src/app/javascriptloader.cpp \
    src/app/keyevents.cpp \
    src/app/main.cpp \
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
    include/webdisplay.h \
    include/keyevents.h \
    include/javascriptloader.h \
    include/constants.h \
    include/applicationwindow.h \
    include/configserverhelp.h \
    include/settingsdialog.h

unix|win32: LIBS += -lX11

# Add the JavaScript source files to build output
# Explanation of the following can be found here:
# https://dragly.org/2013/11/05/copying-data-files-to-the-build-directory-when-working-with-qmake/
include_js_source.commands = $(COPY_DIR) $$PWD/src/js $$OUT_PWD

# Copy over the images
include_js_source.commands = $(COPY_DIR) $$PWD/res $$OUT_PWD

first.depends = $(first) include_js_source
export(first.depends)
export(include_js_source.commands)
QMAKE_EXTRA_TARGETS += first include_js_source

RESOURCES += \
    resources.qrc
