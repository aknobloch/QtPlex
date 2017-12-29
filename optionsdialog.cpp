#include <QFormLayout>
#include <QVBoxLayout>
#include <QLabel>
#include <QLineEdit>
#include <QDialogButtonBox>
#include <QSettings>
#include "optionsdialog.h"
#include "constants.h"

#include <QDebug>

OptionsDialog::OptionsDialog()
{
	initializeLayout();
	setWindowTitle(tr("Plex Server Info"));
}

void OptionsDialog::initializeLayout()
{
	QFormLayout *serverInfoForm = createServerInfoForm();

	QDialogButtonBox *confirmButtons = new QDialogButtonBox(QDialogButtonBox::Ok);
	connect(confirmButtons, &QDialogButtonBox::accepted, this, &OptionsDialog::okPressed);

	QVBoxLayout *parentLayout = new QVBoxLayout();
	parentLayout -> addItem(serverInfoForm);
	parentLayout -> addWidget(confirmButtons);

	setLayout(parentLayout);
	resize(325, 50);
}

QFormLayout * OptionsDialog::createServerInfoForm()
{
	QFormLayout *serverForm = new QFormLayout;

	this -> serverAddress = new QLineEdit;

	serverAddress -> setText(tr("http://192.168.1.25:32400/web"));

	serverForm -> addRow(new QLabel(tr("Server Address:")), serverAddress);

	serverForm -> setHorizontalSpacing(10);
	serverForm -> setVerticalSpacing(5);

	return serverForm;
}

void OptionsDialog::okPressed()
{
	QString enteredAddress = serverAddress -> text();

	QSettings settings;
	settings.setValue(SERVER_ADDRESS_KEY, enteredAddress);

	accept();
}

