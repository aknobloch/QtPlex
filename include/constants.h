#ifndef CONSTANTS_H
#define CONSTANTS_H
#include <QString>

static const QString ORG_NAME = "AaronDevelops";
static const QString APP_NAME = "QtPlex";
static const QString SERVER_ADDRESS_KEY = "ServerAddress";
// whether the web page should log all the JS console
static const bool LOG_JS_CONSOLE = false;
// the tag that is expected to be present on JS logs from us
static const QString JS_QTPLEX_TAG = "[QtPlex]";
static const int MAX_NOTIFICATION_LINE_LENGTH = 30;
static const int EXIT_CODE_FAILURE = 1;

#endif  // CONSTANTS_H
