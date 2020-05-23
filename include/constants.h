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

#endif  // CONSTANTS_H
