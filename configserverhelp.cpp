#include <QWidget>
#include <QVBoxLayout>
#include <QLabel>
#include <QPushButton>
#include "configserverhelp.h"

#include <QDebug>

ConfigServerHelpScreen::ConfigServerHelpScreen(QWidget *parent) : QWidget(parent)
{
	initializeLayout();
}

void ConfigServerHelpScreen::initializeLayout()
{
	QVBoxLayout *parentLayout = new QVBoxLayout();

	QLabel *bannerLabel = createBanner();
	QLabel *infoLabel = createInfoLabel();
	QPushButton *configButton = createConfigButton();

	parentLayout -> addWidget(bannerLabel);
	parentLayout -> addWidget(infoLabel);
	parentLayout -> addWidget(configButton);

	parentLayout -> setAlignment(bannerLabel, Qt::AlignHCenter | Qt::AlignTop);
	parentLayout -> setAlignment(infoLabel, Qt::AlignHCenter | Qt::AlignTop);

	setLayout(parentLayout);
}

QLabel* ConfigServerHelpScreen::createBanner()
{
	QImage *bannerImage = new QImage(":/images/raw resources/banner.png");
	QLabel *bannerLabel = new QLabel();
	bannerLabel -> setPixmap(QPixmap::fromImage(*bannerImage));

	return bannerLabel;
}

QLabel* ConfigServerHelpScreen::createInfoLabel()
{
	QLabel *infoLabel = new QLabel();
	infoLabel -> setText("<font color='#cc7c19'>Looks like you don't have a server configured.</font>");
	QFont infoFont("Arial", 28, QFont::Bold);
	infoLabel->setFont(infoFont);

	return infoLabel;
}

QPushButton* ConfigServerHelpScreen::createConfigButton()
{
	QPushButton *configButton = new QPushButton();
	configButton -> setText("Config Server");

	connect(configButton, &QPushButton::clicked, this, &ConfigServerHelpScreen::configButtonPressed);

	return configButton;
}

void ConfigServerHelpScreen::configButtonPressed()
{
	emit notifyConfigButtonPressed();
}
