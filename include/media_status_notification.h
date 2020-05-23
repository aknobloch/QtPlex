#ifndef POPUP_H
#define POPUP_H

#include <QGridLayout>
#include <QLabel>
#include <QPropertyAnimation>
#include <QTimer>
#include <QWidget>
#include <memory>

// Credit to https://evileg.com/en/post/146/
class MediaStatusNotification : public QWidget {
  Q_OBJECT
  Q_PROPERTY(float popupOpacity READ getPopupOpacity WRITE setPopupOpacity)

  void setPopupOpacity(float opacity);
  float getPopupOpacity() const;

 public:
  MediaStatusNotification();
  ~MediaStatusNotification();

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
  std::unique_ptr<QTimer> timer;
};

#endif  // POPUP_H
