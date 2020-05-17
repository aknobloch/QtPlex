#include "../../include/plex_web_page.h"
#include "../../include/constants.h"
#include "../../include/javascript_loader.h"
#include <QDebug>

PlexWebPage::PlexWebPage() {

  if (LOG_JS_CONSOLE == false) {

    qWarning() << "Disabling JS console logging.";
  }

  isLoaded = false;
  mediaStatusNotifier = new MediaStatusNotification();

  // Title change indicates that playback state has changed
  connect(this, SIGNAL(titleChanged(const QString)), this,
          SLOT(notifyTitleChanged(const QString &)));

  // Used to avoid crashing by emitting notifications before loaded
  connect(this, SIGNAL(loadFinished(bool)), this, SLOT(finishedLoading(bool)));
}

PlexWebPage::~PlexWebPage() = default;

void PlexWebPage::finishedLoading(bool success) { isLoaded = success; }

void PlexWebPage::stopPlayback() {

  QString jsFunction = JavaScriptLoader::loadScriptByName("executeStop.js");
  this->runJavaScript(jsFunction);
}

void PlexWebPage::togglePlayback() {

  QString jsFunction =
      JavaScriptLoader::loadScriptByName("executePlayPause.js");
  this->runJavaScript(jsFunction);
}

void PlexWebPage::forwardTrack() {

  QString jsFunction = JavaScriptLoader::loadScriptByName("executeForward.js");
  this->runJavaScript(jsFunction);
}

void PlexWebPage::previousTrack() {

  QString jsFunction = JavaScriptLoader::loadScriptByName("executePrevious.js");
  this->runJavaScript(jsFunction);
}

void PlexWebPage::notifyTitleChanged(const QString &title) {

  if (isLoaded == false) {

    qDebug() << "Title changed, but skipping due "
                "to page not being done loading.";
    return;
  }

  if (isMediaPlaybackTitle(title) == false) {

    qWarning() << "Title changed, but skipping since it "
                  "does not appear to indicate media playback.";
    return;
  }

  if (this->view()->isActiveWindow()) {

    qDebug() << "Title changed, but skipping since "
                "page is currently active.";
    return;
  }

  mediaStatusNotifier->notify(parseNotificationFromTitle(title));
}

bool PlexWebPage::isMediaPlaybackTitle(const QString &title) {

  QRegularExpression playbackRegex("▶ (.+)-(.+)");
  return playbackRegex.match(title).hasMatch();
}

QString PlexWebPage::parseNotificationFromTitle(const QString &title) {

  QStringList splitTitle = title.split("-");

  // Parse the artist name
  QString artist = splitTitle.first();
  artist = artist.mid(artist.indexOf("▶") + 1);

  if (artist.length() > MAX_NOTIFICATION_LINE_LENGTH) {
    artist = artist.left(MAX_NOTIFICATION_LINE_LENGTH - 3) + "...";
  }

  // Parse the track name
  QString track = splitTitle.last();

  if (track.length() > MAX_NOTIFICATION_LINE_LENGTH) {
    track = track.left(MAX_NOTIFICATION_LINE_LENGTH - 3) + "...";
  }

  return "<b>" + track +
         "</b>"
         "<br>" +
         artist;
}

void PlexWebPage::javaScriptConsoleMessage(JavaScriptConsoleMessageLevel level,
                                           const QString &message,
                                           int lineNumber,
                                           const QString &sourceID) {

  if (LOG_JS_CONSOLE == false) {
    return;
  }

  switch (level) {

  case QWebEnginePage::InfoMessageLevel:
    qDebug() << message + " at " + lineNumber + " by source ID " + sourceID;
    break;
  case QWebEnginePage::WarningMessageLevel:
    qInfo() << message + " at " + lineNumber + " by source ID " + sourceID;
    break;
  case QWebEnginePage::ErrorMessageLevel:
    qWarning() << message + " at " + lineNumber + " by source ID " + sourceID;
    break;
  default:
    break;
  }
}
