#ifndef LOGFILTERWEBPAGE_H
#define LOGFILTERWEBPAGE_H
#include <Qt>
#include <QtWebEngine/QtWebEngine>
#include <QWebEngineView>

class LogFilterWebPage : public QWebEnginePage {

public:
    LogFilterWebPage();
    virtual void javaScriptConsoleMessage(JavaScriptConsoleMessageLevel level, const QString &message, int lineNumber, const QString &sourceID);
};
#endif // LOGFILTERWEBPAGE_H
