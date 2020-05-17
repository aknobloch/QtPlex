#include "../../include/settings_dialog.h"
#include "../../include/constants.h"
#include <QDialogButtonBox>
#include <QFormLayout>
#include <QLabel>
#include <QLineEdit>
#include <QSettings>
#include <QVBoxLayout>

#include <QDebug>

SettingsDialog::SettingsDialog() {
  initializeLayout();
  setWindowTitle(tr("Plex Server Info"));
}

void SettingsDialog::initializeLayout() {
  QFormLayout *serverInfoForm = createServerInfoForm();

  QDialogButtonBox *confirmButtons = new QDialogButtonBox(QDialogButtonBox::Ok);
  connect(confirmButtons, &QDialogButtonBox::accepted, this,
          &SettingsDialog::okPressed);

  QVBoxLayout *parentLayout = new QVBoxLayout();
  parentLayout->addItem(serverInfoForm);
  parentLayout->addWidget(confirmButtons);

  setLayout(parentLayout);
  resize(325, 50);
}

QFormLayout *SettingsDialog::createServerInfoForm() {
  QFormLayout *serverForm = new QFormLayout;

  this->serverAddress = new QLineEdit;

  QSettings settings;
  QString userServerAddress = settings.value(SERVER_ADDRESS_KEY).toString();

  if (userServerAddress.isNull()) {
    serverAddress->setText(tr("http://192.168.1.25:32400/web"));
  } else {
    serverAddress->setText(userServerAddress);
  }

  serverForm->addRow(new QLabel(tr("Server Address:")), serverAddress);

  serverForm->setHorizontalSpacing(10);
  serverForm->setVerticalSpacing(5);

  return serverForm;
}

void SettingsDialog::okPressed() {
  QString enteredAddress = serverAddress->text();

  QSettings settings;
  settings.setValue(SERVER_ADDRESS_KEY, enteredAddress);

  accept();
}
