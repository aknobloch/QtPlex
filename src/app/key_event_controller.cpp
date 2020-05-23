#include "key_event_controller.h"

#include <QDebug>
#include <QObject>
#include <QWebEngineView>
#include <QtWebEngine/QtWebEngine>
#include <memory>

KeyEventController::KeyEventController() {
  media_stop_hotkey_ =
      std::make_unique<QHotkey>(QKeySequence(Qt::Key_MediaStop), true, this);
  media_prev_hotkey_ = std::make_unique<QHotkey>(
      QKeySequence(Qt::Key_MediaPrevious), true, this);
  media_play_hotkey_ =
      std::make_unique<QHotkey>(QKeySequence(Qt::Key_MediaPlay), true, this);
  media_next_hotkey_ =
      std::make_unique<QHotkey>(QKeySequence(Qt::Key_MediaNext), true, this);

  connect(media_stop_hotkey_.get(), &QHotkey::activated, this,
          &KeyEventController::stopKeyActivated);
  connect(media_prev_hotkey_.get(), &QHotkey::activated, this,
          &KeyEventController::prevKeyActivated);
  connect(media_play_hotkey_.get(), &QHotkey::activated, this,
          &KeyEventController::playKeyActivated);
  connect(media_next_hotkey_.get(), &QHotkey::activated, this,
          &KeyEventController::nextKeyActivated);

  bool all_keys_registered = media_stop_hotkey_->isRegistered() &&
                             media_prev_hotkey_->isRegistered() &&
                             media_play_hotkey_->isRegistered() &&
                             media_next_hotkey_->isRegistered();

  qInfo() << "Hotkeys registered: " << all_keys_registered;
}

KeyEventController::~KeyEventController() = default;

void KeyEventController::stopKeyActivated() {
  qDebug() << "Stop key event received.";
  emit stopPressed();
}

void KeyEventController::prevKeyActivated() {
  qDebug() << "Previous key event received.";
  emit prevPressed();
}

void KeyEventController::playKeyActivated() {
  qDebug() << "Play/Pause key event received.";
  emit playPressed();
}

void KeyEventController::nextKeyActivated() {
  qDebug() << "Next key event received.";
  emit nextPressed();
}
