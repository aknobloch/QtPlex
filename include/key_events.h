#ifndef KEYEVENTTHREAD_H
#define KEYEVENTTHREAD_H

#include <QtWebEngine/QtWebEngine>
#include <QWebEngineView>
#include <QObject>
#include "plex_web_page.h"

class KeyEventController : public QObject
{
    Q_OBJECT

private:
    PlexWebPage *plexWebPage;
    int pageReady;

public:
    KeyEventController(PlexWebPage *view);
    ~KeyEventController();
            void startKeyEventService();

    public slots:
    void pageLoaded(int loadSuccessful);
            void stopPressed();
            void prevPressed();
            void playPressed();
            void nextPressed();
};

#endif // KEYEVENTTHREAD_H
