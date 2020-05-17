
#include <QtWebEngine/QtWebEngine>
#include <QWebEngineView>
#include <QObject>
#include <QDebug>
#include <QHotkey>
#include <memory>
#include "../../include/keyevents.h"
#include "../../include/javascript_loader.h"

KeyEventController::~KeyEventController() = default;

KeyEventController::KeyEventController(PlexWebPage *page)
{
    this -> plexWebPage = page;
	this -> pageReady = 0;
    this -> statusNotifier = new MediaStatusNotification();

    connect(plexWebPage, &PlexWebPage::loadFinished, this, &KeyEventController::pageLoaded);
}

void KeyEventController::startKeyEventService()
{
	auto mediaStop = new QHotkey(QKeySequence(Qt::Key_MediaStop), true, this);
	auto mediaPrev = new QHotkey(QKeySequence(Qt::Key_MediaPrevious), true, this);
	auto mediaPlay = new QHotkey(QKeySequence(Qt::Key_MediaPlay), true, this);
	auto mediaNext = new QHotkey(QKeySequence(Qt::Key_MediaNext), true, this);

	qInfo() << "Stop registered: " << mediaStop->isRegistered();
	qInfo() << "Prev registered: " << mediaPrev->isRegistered();
	qInfo() << "Play registered: " << mediaPlay->isRegistered();
	qInfo() << "Next registered: " << mediaNext->isRegistered();

	connect(mediaStop, &QHotkey::activated, this, &KeyEventController::stopPressed);
	connect(mediaPrev, &QHotkey::activated, this, &KeyEventController::prevPressed);
	connect(mediaPlay, &QHotkey::activated, this, &KeyEventController::playPressed);
	connect(mediaNext, &QHotkey::activated, this, &KeyEventController::nextPressed);

	qInfo() << "Key Event service started.";
}

void KeyEventController::executeKey(Qt::Key keyPressed)
{
	if(pageReady != 1)
	{
		qInfo() << "Page not loaded, media key ignored.";
		return;
	}

    QString javaScript = JavaScriptLoader::loadScriptByKeycode(keyPressed);
    plexWebPage->runJavaScript(javaScript);
}

void KeyEventController::stopPressed()
{
    qInfo() << "Stop key pressed.";
	executeKey(Qt::Key_MediaStop);
}

void KeyEventController::prevPressed()
{
    qInfo() << "Previous key pressed.";
	executeKey(Qt::Key_MediaPrevious);
    statusNotifier->notify(plexWebPage->getCurrentPlaybackInfo());
}

void KeyEventController::playPressed()
{
    qInfo() << "Play/Pause key pressed.";
	executeKey(Qt::Key_MediaPlay);
}

void KeyEventController::nextPressed()
{
    qInfo() << "Next key pressed.";
	executeKey(Qt::Key_MediaNext);
    statusNotifier->notify(plexWebPage->getCurrentPlaybackInfo());
}

void KeyEventController::pageLoaded(int loadSuccessful)
{
	QString status = "Successful";

	if(loadSuccessful == 0)
	{
		status = "Unsuccessful";
	}

	qInfo() << status + " page load.";
    startKeyEventService();
	this -> pageReady = loadSuccessful;
}
