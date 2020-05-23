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

void PlexWebPage::finishInitialization(bool is_page_loaded) {
  if (is_page_loaded == false) {
    qFatal("Page failed to load!");
    QApplication::exit(EXIT_CODE_FAILURE);
  }

  loadAndRunScript("commonLibrary.js");
}

void PlexWebPage::stopPlayback() { loadAndRunScript("executeStop.js"); }

void PlexWebPage::togglePlayback() { loadAndRunScript("executePlayPause.js"); }

void PlexWebPage::forwardTrack() { loadAndRunScript("executeForward.js"); }

void PlexWebPage::previousTrack() { loadAndRunScript("executePrevious.js"); }

void PlexWebPage::loadAndRunScript(QString script_name) {
  auto validate_execution_callback = [script_name](const QVariant &result) {
    bool was_execution_successful = result.toString() == "true";
    if (!was_execution_successful) {
      qWarning() << "Failed to execute script " + script_name;
    }
  };

  QString js_function = JavaScriptLoader::loadScriptByName(script_name);
  this->runJavaScript(js_function, QWebEngineScript::ApplicationWorld,
                      validate_execution_callback);
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
  QRegularExpression check_if_playing_regex("▶ (.+)-(.+)");
  return check_if_playing_regex.match(title).hasMatch();
}

QString PlexWebPage::parseNotificationFromTitle(const QString &title) {
  QStringList split_title = title.split("-");

  // Parse the artist name
  QString artist = split_title.first();
  artist = artist.mid(artist.indexOf("▶") + 1);

  if (artist.length() > MAX_NOTIFICATION_LINE_LENGTH) {
    artist = artist.left(MAX_NOTIFICATION_LINE_LENGTH - 3) + "...";
  }

  // Parse the track name
  QString track = split_title.last();

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
  bool is_qtplex_log =
      message.startsWith(JS_QTPLEX_TAG, Qt::CaseSensitivity::CaseInsensitive);

  // If it isn't a QtPlex log and JS logging is disabled, discard.
  if (is_qtplex_log == false && LOG_JS_CONSOLE == false) {
    return;
  }

  if (is_qtplex_log) {
    qInfo() << "JS Console: " << message.mid(JS_QTPLEX_TAG.length() + 1);
  } else {
    qDebug() << message;
  }
}
