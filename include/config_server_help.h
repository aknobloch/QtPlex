#ifndef HELPWIDGET_H
#define HELPWIDGET_H

#include <QLabel>
#include <QPushButton>
#include <QWidget>
#include <memory>

class ConfigServerHelpScreen : public QWidget {
  Q_OBJECT
 public:
  ConfigServerHelpScreen();
  ~ConfigServerHelpScreen();

 private:
  void initializeLayout();
  std::unique_ptr<QLabel> createBanner();
  std::unique_ptr<QLabel> createInfoLabel();
  std::unique_ptr<QPushButton> createConfigButton();

 signals:
  void notifyConfigButtonPressed();

 public slots:
  void configButtonPressed();
};

#endif  // HELPWIDGET_H
