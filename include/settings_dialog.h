#ifndef OPTIONSDIALOG_H
#define OPTIONSDIALOG_H

#include <QDialog>
#include <QFormLayout>
#include <QLineEdit>

class SettingsDialog : public QDialog {
  Q_OBJECT

public:
  SettingsDialog();
  void initializeLayout();

private:
  QLineEdit *serverAddress;

  QFormLayout *createServerInfoForm();

public slots:
  void okPressed();
};

#endif // OPTIONSDIALOG_H
