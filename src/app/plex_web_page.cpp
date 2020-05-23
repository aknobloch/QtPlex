#include "plex_web_page.h"

#include <QApplication>
#include <QDebug>
#include <QWebEngineScript>

#include "constants.h"
#include "javascript_loader.h"

PlexWebPage::PlexWebPage() {
  if (LOG_JS_CONSOLE == false) {
    qWarning() << "Disabling general JS console logging.";
  }

  media_status_notifier_ = std::make_unique<MediaStatusNotification>();
  key_event_controller_ = std::make_unique<KeyEventController>();

  // Setup hotkey event listeners
  connect(key_event_controller_.get(), &KeyEventController::nextPressed, this,
          &PlexWebPage::forwardTrack);
  connect(key_event_controller_.get(), &KeyEventController::prevPressed, this,
          &PlexWebPage::previousTrack);
  connect(key_event_controller_.get(), &KeyEventController::stopPressed, this,
          &PlexWebPage::stopPlayback);
  connect(key_event_controller_.get(), &KeyEventController::playPressed, this,
          &PlexWebPage::togglePlayback);

  // Title change indicates that playback state has changed
  connect(this, SIGNAL(titleChanged(const QString)), this,
          SLOT(notifyTitleChanged(const QString &)));

  // Initialize once finished loading
  connect(this, SIGNAL(loadFinished(bool)), this,
          SLOT(finishInitialization(bool)));
}

PlexWebPage::~PlexWebPage() = default;

void PlexWebPage::finishInitialization(bool isPageLoaded) {
  if (isPageLoaded == false) {
    qFatal("Page failed to load!");
    QApplication::exit(EXIT_CODE_FAILURE);
  }

  loadAndRunScript("commonLibrary.js");
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
    qDebug() << "Title changed, but skipping since it "
                "does not appear to indicate media playback.";
    return;
  }

  if (this->view()->isActiveWindow()) {
    qDebug() << "Title changed, but skipping since "
                "page is currently active.";
    return;
  }

  media_status_notifier_->notify(parseNotificationFromTitle(title));
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
