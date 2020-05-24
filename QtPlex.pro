#############################################
#       Library Configurations
#############################################
include(third_party/QHotkey/qhotkey.pri)

TEMPLATE = app

QT += qml quick
QT += webengine
QT += webenginewidgets
QT += core
QT += gui x11extras

#############################################
#       CPP Source Configurations
#############################################
QMAKE_CXXFLAGS += -std=c++17
SOURCES += \
    src/app/application_window.cpp \
    src/app/file_loader.cpp \
    src/app/first_time_setup_widget.cpp \
    src/app/key_event_controller.cpp \
    src/app/main.cpp \
    src/app/media_status_notification.cc \
    src/app/plex_web_page.cpp \
    src/app/settings_dialog.cpp

DEFINES += QT_DEPRECATED_WARNINGS
DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x050100

#############################################
#       CPP Header Configurations
#############################################
INCLUDEPATH += "include"
HEADERS += \
    include/application_window.h \
    include/file_loader.h \
    include/first_time_setup_widget.h \
    include/key_event_controller.h \
    include/media_status_notification.h \
    include/plex_web_page.h \
    include/settings_dialog.h \
    include/constants.h

#############################################
#       Extra Resources Configuration
#############################################
RESOURCES += \
    resources.qrc

# Add the JavaScript source files, CSS source files and Static Resources to build output
include_extras.commands = $(COPY_DIR) $$PWD/src/js $$OUT_PWD && $(COPY_DIR) $$PWD/src/css $$OUT_PWD && $(COPY_DIR) $$PWD/res $$OUT_PWD

#############################################
#       Build Configurations
#############################################
# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

# Include X11 for key bindings
unix|win32: LIBS += -lX11

first.depends = $(first) include_extras
export(first.depends)
export(include_extras.commands)
QMAKE_EXTRA_TARGETS += first include_extras
