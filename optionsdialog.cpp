#include <QFormLayout>
#include <QVBoxLayout>
#include <QLabel>
#include <QLineEdit>
#include <QDialogButtonBox>
#include "optionsdialog.h"

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
}

QFormLayout * OptionsDialog::createServerInfoForm()
{
	QFormLayout *serverForm = new QFormLayout;

	this -> serverIP = new QLineEdit;
	this -> serverPort = new QLineEdit;

	serverForm -> addRow(new QLabel(tr("Server IP Address:")), serverIP);
	serverForm -> addRow(new QLabel(tr("Server Port:")), serverPort);

	serverForm -> setHorizontalSpacing(10);
	serverForm -> setVerticalSpacing(5);

	return serverForm;
}

void OptionsDialog::okPressed()
{
	qInfo() << getServerAddress();
}

QString OptionsDialog::getServerAddress()
{
	return serverIP -> text() + ":" + serverPort -> text();
}
