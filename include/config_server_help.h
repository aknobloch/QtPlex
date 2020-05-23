#ifndef HELPWIDGET_H
#define HELPWIDGET_H

#include <QLabel>
#include <QPushButton>
#include <QVBoxLayout>
#include <QWidget>
#include <memory>

class FirstTimeSetupWidget : public QWidget {
  Q_OBJECT
 public:
  FirstTimeSetupWidget();
  ~FirstTimeSetupWidget();

 private:
  void initializeLayout();
  std::unique_ptr<QLabel> createBanner();
  std::unique_ptr<QLabel> createInfoLabel();
  std::unique_ptr<QPushButton> createConfigButton();
  std::unique_ptr<QVBoxLayout> box_container_layout_;

 signals:
  void notifyConfigButtonPressed();

 public slots:
  void configButtonPressed();
};

#endif  // HELPWIDGET_H
