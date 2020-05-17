#include "../../include/config_server_help.h"
#include <QLabel>
#include <QPushButton>
#include <QVBoxLayout>
#include <QWidget>

#include <QDebug>

ConfigServerHelpScreen::ConfigServerHelpScreen(QWidget *parent)
    : QWidget(parent) {
  initializeLayout();
}

void ConfigServerHelpScreen::initializeLayout() {
  QVBoxLayout *parentLayout = new QVBoxLayout();

  QLabel *bannerLabel = createBanner();
  QLabel *infoLabel = createInfoLabel();

  QHBoxLayout *buttonWrapper = new QHBoxLayout();
  QPushButton *configButton = createConfigButton();

  buttonWrapper->addWidget(configButton);
  buttonWrapper->setContentsMargins(0, 75, 0, 0);

  parentLayout->addWidget(bannerLabel);
  parentLayout->addWidget(infoLabel);
  parentLayout->addItem(buttonWrapper);

  parentLayout->setAlignment(bannerLabel, Qt::AlignHCenter | Qt::AlignTop);
  parentLayout->setAlignment(infoLabel, Qt::AlignHCenter | Qt::AlignTop);
  parentLayout->setAlignment(buttonWrapper, Qt::AlignHCenter | Qt::AlignTop);

  parentLayout->setContentsMargins(50, 10, 50, 25);

  setLayout(parentLayout);
}

QLabel *ConfigServerHelpScreen::createBanner() {
  QImage *bannerImage = new QImage(":/images/res/banner.png");
  QLabel *bannerLabel = new QLabel();
  bannerLabel->setPixmap(QPixmap::fromImage(*bannerImage));

  return bannerLabel;
}

QLabel *ConfigServerHelpScreen::createInfoLabel() {
  QLabel *infoLabel = new QLabel();
  infoLabel->setText("<font color='#cc7c19'>Looks like you don't have a server "
                     "configured.</font>");
  QFont infoFont("Arial", 28, QFont::Bold);
  infoLabel->setFont(infoFont);

  return infoLabel;
}

QPushButton *ConfigServerHelpScreen::createConfigButton() {
  QPushButton *configButton = new QPushButton();

  // text properties
  configButton->setText("Config Server");
  QFont buttonFont("Arial", 18, QFont::Bold);
  buttonFont.setCapitalization(QFont::SmallCaps);
  configButton->setFont(buttonFont);

  // button style
  QString roundedButtonStyle = "background-color:rgb(244,244,244);"
                               "border-radius:10px;"
                               "border-width:25px;"
                               "border-color:red;";
  configButton->setStyleSheet(roundedButtonStyle);

  // placement and size
  configButton->setMinimumWidth(200);
  configButton->setMinimumHeight(75);
  configButton->setContentsMargins(100, 100, 100, 100);

  configButton->setFocusPolicy(Qt::NoFocus);

  connect(configButton, &QPushButton::clicked, this,
          &ConfigServerHelpScreen::configButtonPressed);

  return configButton;
}

void ConfigServerHelpScreen::configButtonPressed() {
  emit notifyConfigButtonPressed();
}
