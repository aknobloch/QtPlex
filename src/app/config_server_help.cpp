#include "config_server_help.h"

#include <QDebug>
#include <QLabel>
#include <QPushButton>
#include <QVBoxLayout>
#include <QWidget>

ConfigServerHelpScreen::ConfigServerHelpScreen() { initializeLayout(); }
ConfigServerHelpScreen::~ConfigServerHelpScreen() = default;

void ConfigServerHelpScreen::initializeLayout() {
  QVBoxLayout *parentLayout = new QVBoxLayout();

  std::unique_ptr<QLabel> bannerLabel = createBanner();
  std::unique_ptr<QLabel> infoLabel = createInfoLabel();

  auto buttonWrapper = std::make_unique<QHBoxLayout>();
  std::unique_ptr<QPushButton> configButton = createConfigButton();

  buttonWrapper->addWidget(configButton.release());
  buttonWrapper->setContentsMargins(0, 75, 0, 0);

  parentLayout->addWidget(bannerLabel.get());
  parentLayout->addWidget(infoLabel.get());
  parentLayout->addItem(buttonWrapper.get());

  parentLayout->setAlignment(bannerLabel.release(),
                             Qt::AlignHCenter | Qt::AlignTop);
  parentLayout->setAlignment(infoLabel.release(),
                             Qt::AlignHCenter | Qt::AlignTop);
  parentLayout->setAlignment(buttonWrapper.release(),
                             Qt::AlignHCenter | Qt::AlignTop);

  parentLayout->setContentsMargins(50, 10, 50, 25);

  setLayout(parentLayout);
}

std::unique_ptr<QLabel> ConfigServerHelpScreen::createBanner() {
  auto bannerImage = std::make_unique<QImage>(":/images/res/banner.png");
  auto bannerLabel = std::make_unique<QLabel>();
  bannerLabel->setPixmap(QPixmap::fromImage(*bannerImage));

  return bannerLabel;
}

std::unique_ptr<QLabel> ConfigServerHelpScreen::createInfoLabel() {
  auto infoLabel = std::make_unique<QLabel>();
  infoLabel->setText(
      "<font color='#cc7c19'>Looks like you don't have a server "
      "configured.</font>");
  QFont infoFont("Arial", 28, QFont::Bold);
  infoLabel->setFont(infoFont);

  return infoLabel;
}

std::unique_ptr<QPushButton> ConfigServerHelpScreen::createConfigButton() {
  auto configButton = std::make_unique<QPushButton>();

  // text properties
  configButton->setText("Config Server");
  QFont buttonFont("Arial", 18, QFont::Bold);
  buttonFont.setCapitalization(QFont::SmallCaps);
  configButton->setFont(buttonFont);

  // button style
  QString roundedButtonStyle =
      "background-color:rgb(244,244,244);"
      "border-radius:10px;"
      "border-width:25px;"
      "border-color:red;";
  configButton->setStyleSheet(roundedButtonStyle);

  // placement and size
  configButton->setMinimumWidth(200);
  configButton->setMinimumHeight(75);
  configButton->setContentsMargins(100, 100, 100, 100);

  configButton->setFocusPolicy(Qt::NoFocus);

  connect(configButton.get(), &QPushButton::clicked, this,
          &ConfigServerHelpScreen::configButtonPressed);

  return configButton;
}

void ConfigServerHelpScreen::configButtonPressed() {
  emit notifyConfigButtonPressed();
}
