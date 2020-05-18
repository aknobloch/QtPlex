#ifndef LOGFILTERWEBPAGE_H
#define LOGFILTERWEBPAGE_H
#include "media_status_notification.h"
#include <QObject>
#include <QWebEngineView>
#include <Qt>
#include <QtWebEngine/QtWebEngine>

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
  QString currentPlaybackInfo;
  MediaStatusNotification *mediaStatusNotifier;
  bool pageReady;
  void loadAndRunScript(QString scriptName);
  void refreshCurrentPlaybackInfo();
  bool isMediaPlaybackTitle(const QString &title);
  QString parseNotificationFromTitle(const QString &title);

private slots:
  /**
   * A title change indicates that the playback status of the
   * internal media has changed, since Plex updates the title with
   * the currently playing track. Janky, but this is the only reliable
   * way I could find to react to changing songs.
   */
  void notifyTitleChanged(const QString &title);
  void finishedLoading(bool isSuccess);
};
#endif // LOGFILTERWEBPAGE_H
