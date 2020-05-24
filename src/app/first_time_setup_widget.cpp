#include "first_time_setup_widget.h"

#include <QDebug>
#include <QLabel>
#include <QPushButton>
#include <QVBoxLayout>
#include <QWidget>

FirstTimeSetupWidget::FirstTimeSetupWidget() { initializeLayout(); }
FirstTimeSetupWidget::~FirstTimeSetupWidget() = default;

void FirstTimeSetupWidget::initializeLayout() {
  box_container_layout_ = std::make_unique<QVBoxLayout>();

  std::unique_ptr<QLabel> bannerLabel = createBanner();
  std::unique_ptr<QLabel> infoLabel = createInfoLabel();

  auto buttonWrapper = std::make_unique<QHBoxLayout>();
  std::unique_ptr<QPushButton> configButton = createConfigButton();

  buttonWrapper->addWidget(configButton.release());
  buttonWrapper->setContentsMargins(0, 75, 0, 0);

  box_container_layout_->addWidget(bannerLabel.get());
  box_container_layout_->addWidget(infoLabel.get());
  box_container_layout_->addItem(buttonWrapper.get());

  box_container_layout_->setAlignment(bannerLabel.release(),
                                      Qt::AlignHCenter | Qt::AlignTop);
  box_container_layout_->setAlignment(infoLabel.release(),
                                      Qt::AlignHCenter | Qt::AlignTop);
  box_container_layout_->setAlignment(buttonWrapper.release(),
                                      Qt::AlignHCenter | Qt::AlignTop);

  box_container_layout_->setContentsMargins(50, 10, 50, 25);

  setLayout(box_container_layout_.get());
}

std::unique_ptr<QLabel> FirstTimeSetupWidget::createBanner() {
  auto banner_image = std::make_unique<QImage>(":/images/res/banner.png");
  auto banner_label = std::make_unique<QLabel>();
  banner_label->setPixmap(QPixmap::fromImage(*banner_image));

  return banner_label;
}

std::unique_ptr<QLabel> FirstTimeSetupWidget::createInfoLabel() {
  auto info_label = std::make_unique<QLabel>();
  info_label->setText(
      "<font color='#cc7c19'>Looks like you don't have a server "
      "configured.</font>");
  QFont info_font("Arial", 28, QFont::Bold);
  info_label->setFont(info_font);

  return info_label;
}

std::unique_ptr<QPushButton> FirstTimeSetupWidget::createConfigButton() {
  auto config_button = std::make_unique<QPushButton>();

  // text properties
  config_button->setText("Config Server");
  QFont buttonFont("Arial", 18, QFont::Bold);
  buttonFont.setCapitalization(QFont::SmallCaps);
  config_button->setFont(buttonFont);

  // button style
  QString roundedButtonStyle =
      "background-color:rgb(244,244,244);"
      "border-radius:10px;"
      "border-width:25px;"
      "border-color:red;";
  config_button->setStyleSheet(roundedButtonStyle);

  // placement and size
  config_button->setMinimumWidth(200);
  config_button->setMinimumHeight(75);
  config_button->setContentsMargins(100, 100, 100, 100);

  config_button->setFocusPolicy(Qt::NoFocus);

  connect(config_button.get(), &QPushButton::clicked, this,
          &FirstTimeSetupWidget::configButtonPressed);

  return config_button;
}

void FirstTimeSetupWidget::configButtonPressed() {
  emit notifyConfigButtonPressed();
}
