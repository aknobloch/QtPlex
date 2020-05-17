#ifndef LOGFILTERWEBPAGE_H
#define LOGFILTERWEBPAGE_H
#include <Qt>
#include <QtWebEngine/QtWebEngine>
#include <QWebEngineView>

class PlexWebPage : public QWebEnginePage {

public:
    PlexWebPage();
    QString getCurrentPlaybackInfo();
    virtual void javaScriptConsoleMessage(JavaScriptConsoleMessageLevel level, const QString &message, int lineNumber, const QString &sourceID);

private:
    QString currentPlaybackInfo;
    void refreshCurrentPlaybackInfo();
};
#endif // LOGFILTERWEBPAGE_H
