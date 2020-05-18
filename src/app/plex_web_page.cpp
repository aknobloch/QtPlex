#include "../../include/plex_web_page.h"
#include "../../include/constants.h"
#include "../../include/javascript_loader.h"
#include <QApplication>
#include <QDebug>
#include <QWebEngineScript>

PlexWebPage::PlexWebPage() {

  if (LOG_JS_CONSOLE == false) {

    qWarning() << "Disabling general JS console logging.";
  }

  pageReady = false;
  mediaStatusNotifier = new MediaStatusNotification();

  // Title change indicates that playback state has changed
  connect(this, SIGNAL(titleChanged(const QString)), this,
          SLOT(notifyTitleChanged(const QString &)));

  // Initialize once finished loading
  connect(this, SIGNAL(loadFinished(bool)), this, SLOT(finishedLoading(bool)));
}

PlexWebPage::~PlexWebPage() = default;

void PlexWebPage::finishedLoading(bool isSuccess) {

  if (isSuccess == false) {

    qFatal("Page failed to load!");
    QApplication::exit(EXIT_CODE_FAILURE);
  }

  loadAndRunScript("commonLibrary.js");
  pageReady = true;
}

void PlexWebPage::stopPlayback() { loadAndRunScript("executeStop.js"); }

void PlexWebPage::togglePlayback() { loadAndRunScript("executePlayPause.js"); }

void PlexWebPage::forwardTrack() { loadAndRunScript("executeForward.js"); }

void PlexWebPage::previousTrack() { loadAndRunScript("executePrevious.js"); }

void PlexWebPage::loadAndRunScript(QString scriptName) {

  auto validateExecution = [scriptName](const QVariant &result) {
    bool isSuccessful = result.toString() == "true";

    if (isSuccessful == false) {
      qWarning() << "Failed to execute script " + scriptName;
    }
  };

  QString jsFunction = JavaScriptLoader::loadScriptByName(scriptName);
  this->runJavaScript(jsFunction, QWebEngineScript::ApplicationWorld,
                      validateExecution);
}

void PlexWebPage::notifyTitleChanged(const QString &title) {

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

void PlexWebPage::javaScriptConsoleMessage(JavaScriptConsoleMessageLevel,
                                           const QString &message, int,
                                           const QString &) {

  bool isQtPlexLog =
      message.startsWith(JS_QTPLEX_TAG, Qt::CaseSensitivity::CaseInsensitive);

  // If it isn't a QtPlex log and JS logging is disabled, discard.
  if (isQtPlexLog == false && LOG_JS_CONSOLE == false) {
    return;
  }

  if (isQtPlexLog) {
    qInfo() << "JS Console: " << message.mid(JS_QTPLEX_TAG.length() + 1);
  } else {
    qDebug() << message;
  }
}
