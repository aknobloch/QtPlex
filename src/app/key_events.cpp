
#include <QtWebEngine/QtWebEngine>
#include <QWebEngineView>
#include <QObject>
#include <QDebug>
#include <QHotkey>
#include <memory>
#include "../../include/key_events.h"

KeyEventController::~KeyEventController() = default;

KeyEventController::KeyEventController(PlexWebPage *page)
{
    this -> plexWebPage = page;
	this -> pageReady = 0;

    connect(plexWebPage, &PlexWebPage::loadFinished, this, &KeyEventController::pageLoaded);
}

void KeyEventController::startKeyEventService()
{
	auto mediaStop = new QHotkey(QKeySequence(Qt::Key_MediaStop), true, this);
	auto mediaPrev = new QHotkey(QKeySequence(Qt::Key_MediaPrevious), true, this);
	auto mediaPlay = new QHotkey(QKeySequence(Qt::Key_MediaPlay), true, this);
	auto mediaNext = new QHotkey(QKeySequence(Qt::Key_MediaNext), true, this);

    bool allKeysRegistered =
        mediaStop->isRegistered() &&
        mediaPrev->isRegistered() &&
        mediaPlay->isRegistered() &&
        mediaNext->isRegistered();

    qInfo() << "Hotkeys registered: " << allKeysRegistered;

	connect(mediaStop, &QHotkey::activated, this, &KeyEventController::stopPressed);
	connect(mediaPrev, &QHotkey::activated, this, &KeyEventController::prevPressed);
	connect(mediaPlay, &QHotkey::activated, this, &KeyEventController::playPressed);
	connect(mediaNext, &QHotkey::activated, this, &KeyEventController::nextPressed);

	qInfo() << "Key Event service started.";
}

void KeyEventController::stopPressed()
{
    qDebug() << "Stop key event received.";
    plexWebPage->stopPlayback();
}

void KeyEventController::prevPressed()
{
    qDebug() << "Previous key event received.";
    plexWebPage->previousTrack();
}

void KeyEventController::playPressed()
{
    qDebug() << "Play/Pause key event received.";
    plexWebPage->togglePlayback();
}

void KeyEventController::nextPressed()
{
    qDebug() << "Next key event received.";
    plexWebPage->forwardTrack();
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
