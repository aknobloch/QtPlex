#ifndef KEYEVENTTHREAD_H
#define KEYEVENTTHREAD_H

#include "media_status_notification.h"
#include "plex_web_page.h"
#include <QObject>
#include <QWebEngineView>
#include <QtWebEngine/QtWebEngine>

class KeyEventController : public QObject {
  Q_OBJECT

private:
  PlexWebPage *plexWebPage;
  MediaStatusNotification *statusNotifier;
  int pageReady;

public:
  KeyEventController(PlexWebPage *view);
  ~KeyEventController();
  void startKeyEventService();

public slots:
  void pageLoaded(int loadSuccessful);
  void executeKey(Qt::Key keyPressed);
  void stopPressed();
  void prevPressed();
  void playPressed();
  void nextPressed();
};

#endif // KEYEVENTTHREAD_H
