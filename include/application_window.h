#ifndef APPLICATIONWINDOW_H
#define APPLICATIONWINDOW_H

#include <QMainWindow>

#include "key_event_controller.h"

class ApplicationWindow : public QMainWindow {
  Q_OBJECT

 public:
  ApplicationWindow();
  ~ApplicationWindow();
  void show();

 private:
  std::unique_ptr<QWebEngineView> web_engine_view_;

  void initializeCentralWidget();
  void initializeMenuBar();
  void initializeWebEngineView(QString serverAddress);
  void setHelpWindow();
  bool showingHelpScreen();

 signals:

 public slots:
  void showSettingsDialog();
};

#endif  // APPLICATIONWINDOW_H
