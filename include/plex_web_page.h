#ifndef PLEXWEBPAGE_H
#define PLEXWEBPAGE_H

#include <QObject>
#include <QWebEngineView>
#include <Qt>
#include <QtWebEngine/QtWebEngine>

#include "key_event_controller.h"
#include "media_status_notification.h"

class PlexWebPage : public QWebEnginePage {
  Q_OBJECT

 public:
  PlexWebPage();
  ~PlexWebPage();
  void stopPlayback();
  void togglePlayback();
  void forwardTrack();
  void previousTrack();
  virtual void javaScriptConsoleMessage(JavaScriptConsoleMessageLevel,
                                        const QString &message, int,
                                        const QString &);

 private:
  bool isMediaPlaybackTitle(const QString &title);
  void loadAndRunScript(QString scriptName);
  QString parseNotificationFromTitle(const QString &title);
  void refreshCurrentPlaybackInfo();
  QString current_playback_info_;
  std::unique_ptr<KeyEventController> key_event_controller_;
  std::unique_ptr<MediaStatusNotification> media_status_notifier_;

 private slots:
  void finishInitialization(bool isSuccess);
  /**
   * A title change indicates that the playback status of the
   * internal media has changed, since Plex updates the title with
   * the currently playing track. Janky, but this is the only reliable
   * way I could find to react to changing songs.
   */
  void notifyTitleChanged(const QString &title);
};
#endif  // PLEXWEBPAGE_H
