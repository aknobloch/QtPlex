#include "../../include/plex_web_page.h"
#include "../../include/constants.h"
#include "../../include/javascript_loader.h"
#include <QDebug>

PlexWebPage::PlexWebPage() {
    if(LOG_JS_CONSOLE == false) {

        qWarning() << "Disabling JS console logging.";
    }
}

void PlexWebPage::refreshCurrentPlaybackInfo() {

    QString jsFunction = JavaScriptLoader::loadScriptByName("listenForTitleChange.js");

    this->runJavaScript(jsFunction, [this](const QVariant &result) {
        this->currentPlaybackInfo = result.toString();
    });
}

QString PlexWebPage::getCurrentPlaybackInfo() {

    refreshCurrentPlaybackInfo();
    return this->currentPlaybackInfo;
}

void PlexWebPage::javaScriptConsoleMessage(
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
