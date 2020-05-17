// Credit to https://evileg.com/en/post/146/

#include "../../include/media_status_notification.h"
#include <QPainter>
#include <QApplication>
#include <QDesktopWidget>
#include <QDebug>
<<<<<<< HEAD
#include <QScreen>
#include <QWindow>
=======
>>>>>>> b67aacebd7353ec510d6a75591d8a53df1bbbcd2

MediaStatusNotification::MediaStatusNotification(QWidget *parent) : QWidget(parent)
{
    setWindowFlags(Qt::FramelessWindowHint |        // Disable window decoration
                   Qt::Tool |                       // Discard display in a separate window
                   Qt::WindowStaysOnTopHint);       // Set on top of all windows
    setAttribute(Qt::WA_TranslucentBackground);     // Indicates that the background will be transparent
    setAttribute(Qt::WA_ShowWithoutActivating);     // At the show, the widget does not get the focus automatically

    animation.setTargetObject(this);                // Set the target animation
    animation.setPropertyName("popupOpacity");      //
    connect(&animation, &QAbstractAnimation::finished, this, &MediaStatusNotification::hide);

    label.setAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
    label.setStyleSheet("QLabel { color : white; "
                        "margin-top: 6px;"
                        "margin-bottom: 6px;"
                        "margin-left: 10px;"
                        "margin-right: 10px; }");

    layout.addWidget(&label, 0, 0);
    setLayout(&layout);

    timer = new QTimer();
    connect(timer, &QTimer::timeout, this, &MediaStatusNotification::hideAnimation);
}

void MediaStatusNotification::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event)

    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);

    QRect roundedRect;
    roundedRect.setX(rect().x() + 5);
    roundedRect.setY(rect().y() + 5);
    roundedRect.setWidth(rect().width() - 10);
    roundedRect.setHeight(rect().height() - 10);

    painter.setBrush(QBrush(QColor(0,0,0,180)));
    painter.setPen(Qt::NoPen);

    painter.drawRoundedRect(roundedRect, 10, 10);
}

void MediaStatusNotification::notify(QString text) {
    setPopupText(text);
    show();
}

void MediaStatusNotification::setPopupText(const QString &text)
{
    label.setText(text);    // Set the text in the Label
    adjustSize();           // With the recalculation notice sizes
}

void MediaStatusNotification::show()
{
    setWindowOpacity(0.0);  // Set the transparency to zero

<<<<<<< HEAD
    animation.setDuration(100);     // Configuring the duration of the animation
    animation.setStartValue(0.0);   // The start value is 0 (fully transparent widget)
    animation.setEndValue(1.0);     // End - completely opaque widget
    QRect currentScreenSize = QGuiApplication::primaryScreen()->geometry();

    setGeometry(currentScreenSize.width() - 36 - width() + currentScreenSize.x(),
                currentScreenSize.height() - 36 - height() + currentScreenSize.y(),
=======
    animation.setDuration(150);     // Configuring the duration of the animation
    animation.setStartValue(0.0);   // The start value is 0 (fully transparent widget)
    animation.setEndValue(1.0);     // End - completely opaque widget

    setGeometry(QApplication::desktop()->availableGeometry().width() - 36 - width() + QApplication::desktop() -> availableGeometry().x(),
                QApplication::desktop()->availableGeometry().height() - 36 - height() + QApplication::desktop() -> availableGeometry().y(),
>>>>>>> b67aacebd7353ec510d6a75591d8a53df1bbbcd2
                width(),
                height());
    QWidget::show();

    animation.start();
    timer->start(3000);
}

void MediaStatusNotification::hideAnimation()
{
    timer->stop();
<<<<<<< HEAD
    animation.setDuration(500);
=======
    animation.setDuration(1000);
>>>>>>> b67aacebd7353ec510d6a75591d8a53df1bbbcd2
    animation.setStartValue(1.0);
    animation.setEndValue(0.0);
    animation.start();
}

void MediaStatusNotification::hide()
{
    // If the widget is transparent, then hide it
    if(getPopupOpacity() == 0.0){
        QWidget::hide();
    }
}

void MediaStatusNotification::setPopupOpacity(float opacity)
{
    popupOpacity = opacity;

    setWindowOpacity(opacity);
}

float MediaStatusNotification::getPopupOpacity() const
{
    return popupOpacity;
}
