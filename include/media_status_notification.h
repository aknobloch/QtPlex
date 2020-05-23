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
  Q_PROPERTY(float popup_opacity_ READ getPopupOpacity WRITE setPopupOpacity)

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
  QLabel label_;
  QGridLayout layout_;
  QPropertyAnimation animation_;
  float popup_opacity_;
  std::unique_ptr<QTimer> timer_;
};

#endif  // POPUP_H
