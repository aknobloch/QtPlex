#ifndef CONSTANTS_H
#define CONSTANTS_H
#include <QString>

static const QString kOrganizationName = "AaronDevelops";
static const QString kAppName = "QtPlex";
static const QString kServerAddressKey = "ServerAddress";
// whether the web page should log all the JS console
static const bool kLogJavascriptConsole = false;
// the tag that is expected to be present on JS logs from us
static const QString kJavascriptQtPlexTag = "[QtPlex]";
static const int kMaxNotificationLineLength = 30;
static const int kFailureExitCode = 1;
static const QString kJSFileCommonLibrary = "common_library.js";
static const QString kJSFileExecuteForward = "execute_forward.js";
static const QString kJSFileExecutePlayPause = "execute_play_pause.js";
static const QString kJSFileExecutePrevious = "execute_previous.js";
static const QString kJSFileExecuteStop = "execute_stop.js";

#endif  // CONSTANTS_H
