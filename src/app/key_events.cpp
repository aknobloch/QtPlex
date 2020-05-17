
#include "../../include/key_events.h"
#include <QDebug>
#include <QHotkey>
#include <QObject>
#include <QWebEngineView>
#include <QtWebEngine/QtWebEngine>
#include <memory>

KeyEventController::~KeyEventController() = default;

KeyEventController::KeyEventController(PlexWebPage *page) {
  this->plexWebPage = page;
  connect(plexWebPage, &PlexWebPage::loadFinished, this,
          &KeyEventController::pageLoaded);
}

void KeyEventController::startKeyEventService() {
  auto mediaStop = new QHotkey(QKeySequence(Qt::Key_MediaStop), true, this);
  auto mediaPrev = new QHotkey(QKeySequence(Qt::Key_MediaPrevious), true, this);
  auto mediaPlay = new QHotkey(QKeySequence(Qt::Key_MediaPlay), true, this);
  auto mediaNext = new QHotkey(QKeySequence(Qt::Key_MediaNext), true, this);

  bool allKeysRegistered =
      mediaStop->isRegistered() && mediaPrev->isRegistered() &&
      mediaPlay->isRegistered() && mediaNext->isRegistered();

  qInfo() << "Hotkeys registered: " << allKeysRegistered;

  connect(mediaStop, &QHotkey::activated, this,
          &KeyEventController::stopPressed);
  connect(mediaPrev, &QHotkey::activated, this,
          &KeyEventController::prevPressed);
  connect(mediaPlay, &QHotkey::activated, this,
          &KeyEventController::playPressed);
  connect(mediaNext, &QHotkey::activated, this,
          &KeyEventController::nextPressed);

  qInfo() << "Key Event service started.";
}

void KeyEventController::stopPressed() {
  qDebug() << "Stop key event received.";
  plexWebPage->stopPlayback();
}

void KeyEventController::prevPressed() {
  qDebug() << "Previous key event received.";
  plexWebPage->previousTrack();
}

void KeyEventController::playPressed() {
  qDebug() << "Play/Pause key event received.";
  plexWebPage->togglePlayback();
}

void KeyEventController::nextPressed() {
  qDebug() << "Next key event received.";
  plexWebPage->forwardTrack();
}

void KeyEventController::pageLoaded(bool loadSuccessful) {

  if (loadSuccessful == false) {

    qWarning() << "Failure to load Plex Web Page, aborting key bindings.";
    return;
  }

  startKeyEventService();
}
