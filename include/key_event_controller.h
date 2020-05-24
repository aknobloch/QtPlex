#ifndef KEYEVENTCONTROLLER_H
#define KEYEVENTCONTROLLER_H

#include <QHotkey>
#include <QObject>
#include <QWebEngineView>
#include <QtWebEngine/QtWebEngine>

class KeyEventController : public QObject {
  Q_OBJECT

 public:
  KeyEventController();
  ~KeyEventController();

 private:
  std::unique_ptr<QHotkey> media_stop_hotkey_;
  std::unique_ptr<QHotkey> media_prev_hotkey_;
  std::unique_ptr<QHotkey> media_play_hotkey_;
  std::unique_ptr<QHotkey> media_next_hotkey_;

 public slots:
  void stopKeyActivated();
  void prevKeyActivated();
  void playKeyActivated();
  void nextKeyActivated();

 signals:
  void stopPressed();
  void prevPressed();
  void playPressed();
  void nextPressed();
};

#endif  // KEYEVENTCONTROLLER_H
