#include "settings_dialog.h"

#include <QDebug>
#include <QDialogButtonBox>
#include <QFormLayout>
#include <QLabel>
#include <QLineEdit>
#include <QSettings>
#include <QVBoxLayout>

#include "constants.h"

SettingsDialog::SettingsDialog() {
  initializeLayout();
  setWindowTitle(tr("QtPlex Settings"));
}

void SettingsDialog::initializeLayout() {
  std::unique_ptr<QFormLayout> serverInfoForm = createServerInfoForm();

  QDialogButtonBox *confirmButtons = new QDialogButtonBox(QDialogButtonBox::Ok);
  connect(confirmButtons, &QDialogButtonBox::accepted, this,
          &SettingsDialog::okPressed);

  auto parentLayout = std::make_unique<QVBoxLayout>();
  parentLayout->addItem(serverInfoForm.release());
  parentLayout->addWidget(confirmButtons);

  setLayout(parentLayout.release());
  resize(325, 50);
}

std::unique_ptr<QFormLayout> SettingsDialog::createServerInfoForm() {
  auto serverForm = std::make_unique<QFormLayout>();
  this->server_address_ = std::make_unique<QLineEdit>();

  QSettings settings;
  QString userServerAddress = settings.value(SERVER_ADDRESS_KEY).toString();

  if (userServerAddress.isNull()) {
    server_address_->setText(tr("http://192.168.1.25:32400/web"));
  } else {
    server_address_->setText(userServerAddress);
  }

  serverForm->addRow(new QLabel(tr("Server Address:")), server_address_.get());
  serverForm->setHorizontalSpacing(10);
  serverForm->setVerticalSpacing(5);

  return serverForm;
}

void SettingsDialog::okPressed() {
  QString enteredAddress = server_address_->text();

  QSettings settings;
  settings.setValue(SERVER_ADDRESS_KEY, enteredAddress);

  accept();
}
