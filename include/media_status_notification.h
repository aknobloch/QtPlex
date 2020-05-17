// Credit to https://evileg.com/en/post/146/
#ifndef POPUP_H
#define POPUP_H

#include <QGridLayout>
#include <QLabel>
#include <QPropertyAnimation>
#include <QTimer>
#include <QWidget>

class MediaStatusNotification : public QWidget {
  Q_OBJECT

  Q_PROPERTY(float popupOpacity READ getPopupOpacity WRITE setPopupOpacity)

  void setPopupOpacity(float opacity);
  float getPopupOpacity() const;

public:
  explicit MediaStatusNotification(QWidget *parent = 0);

protected:
  void paintEvent(QPaintEvent *event);

public slots:
  void notify(QString text);

private slots:
  void hideAnimation();
  void show();
  void hide();
  void setPopupText(const QString &text);

private:
  QLabel label;
  QGridLayout layout;
  QPropertyAnimation animation;
  float popupOpacity;
  QTimer *timer;
};

#endif // POPUP_H
