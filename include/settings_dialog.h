#ifndef SETTINGSDIALOG_H
#define SETTINGSDIALOG_H

#include <QDialog>
#include <QFormLayout>
#include <QLineEdit>
#include <memory>

class SettingsDialog : public QDialog {
  Q_OBJECT

 public:
  SettingsDialog();
  void initializeLayout();

 private:
  std::unique_ptr<QFormLayout> createServerInfoForm();
  std::unique_ptr<QLineEdit> server_address_;
  std::unique_ptr<QVBoxLayout> box_container_layout_;

 public slots:
  void okPressed();
};

#endif  // SETTINGSDIALOG_H
