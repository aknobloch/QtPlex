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
  std::unique_ptr<QFormLayout> server_info_form = createServerInfoForm();

  auto confirm_button =
      std::make_unique<QDialogButtonBox>(QDialogButtonBox::Ok);
  connect(confirm_button.get(), &QDialogButtonBox::accepted, this,
          &SettingsDialog::okPressed);

  box_container_layout_ = std::make_unique<QVBoxLayout>();
  box_container_layout_->addItem(server_info_form.release());
  box_container_layout_->addWidget(confirm_button.release());

  setLayout(box_container_layout_.get());
  resize(325, 50);
}

std::unique_ptr<QFormLayout> SettingsDialog::createServerInfoForm() {
  auto server_form = std::make_unique<QFormLayout>();
  server_address_ = std::make_unique<QLineEdit>();

  QSettings settings;
  QString userServerAddress = settings.value(kServerAddressKey).toString();

  if (userServerAddress.isNull()) {
    server_address_->setText(tr("http://192.168.1.25:32400/web"));
  } else {
    server_address_->setText(userServerAddress);
  }

  server_form->addRow(new QLabel(tr("Server Address:")), server_address_.get());
  server_form->setHorizontalSpacing(10);
  server_form->setVerticalSpacing(5);

  return server_form;
}

void SettingsDialog::okPressed() {
  QString entered_address = server_address_->text();

  QSettings settings;
  settings.setValue(kServerAddressKey, entered_address);

  accept();
}
