#include "../../include/logfilterwebpage.h"
#include "../../include/constants.h"
#include <QDebug>

LogFilterWebPage::LogFilterWebPage() {
    if(LOG_JS_CONSOLE == false) {

        qWarning() << "Disabling JS console logging.";
    }
}

void LogFilterWebPage::javaScriptConsoleMessage(
        JavaScriptConsoleMessageLevel level,
        const QString &message,
        int lineNumber,
        const QString &sourceID) {

    if(LOG_JS_CONSOLE == false) {
        return;
    }

    switch(level) {

        case QWebEnginePage::InfoMessageLevel :
            qDebug() << message;
            break;
        case QWebEnginePage::WarningMessageLevel :
            qInfo() << message;
        case QWebEnginePage::ErrorMessageLevel :
            qWarning() << message;
        default:
            break;
    }
}
