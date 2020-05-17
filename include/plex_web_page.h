#ifndef LOGFILTERWEBPAGE_H
#define LOGFILTERWEBPAGE_H
#include <Qt>
#include <QtWebEngine/QtWebEngine>
#include <QWebEngineView>
#include <QObject>
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
    virtual void javaScriptConsoleMessage(JavaScriptConsoleMessageLevel level, const QString &message, int lineNumber, const QString &sourceID);

private:
    QString currentPlaybackInfo;
    MediaStatusNotification* mediaStatusNotifier;
    bool isLoaded;
    void refreshCurrentPlaybackInfo();
    bool isMediaPlaybackTitle(const QString& title);
    QString parseNotificationFromTitle(const QString& title);

private slots:
    void finishedLoading(bool success);

    /**
     * A title change indicates that the playback status of the
     * internal media has changed. Plex will update the title with
     * the currently playing track.
     */
    void notifyTitleChanged(const QString& title);
};
#endif // LOGFILTERWEBPAGE_H
