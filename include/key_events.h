#ifndef KEYEVENTTHREAD_H
#define KEYEVENTTHREAD_H

#include "plex_web_page.h"
#include <QObject>
#include <QWebEngineView>
#include <QtWebEngine/QtWebEngine>

class KeyEventController : public QObject {
  Q_OBJECT

private:
  PlexWebPage *plexWebPage;

public:
  KeyEventController(PlexWebPage *view);
  ~KeyEventController();
  void startKeyEventService();

public slots:
  void pageLoaded(bool loadSuccessful);
  void stopPressed();
  void prevPressed();
  void playPressed();
  void nextPressed();
};

#endif // KEYEVENTTHREAD_H
