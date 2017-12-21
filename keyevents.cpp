
#include <QtWebEngine/QtWebEngine>
#include <QWebEngineView>
#include <QObject>
#include <QDebug>
#include <QHotkey>
#include <keyevents.h>
#include <mediakeys.h>

KeyEventController::KeyEventController(QWebEngineView *view)
{
	this -> plexWebView = view;
	this -> pageReady = 0;

	connect(plexWebView, &QWebEngineView::loadFinished, this, &KeyEventController::pageLoaded);
	startKeyEventService();
}

void KeyEventController::pageLoaded(int loadSuccessful)
{
	qInfo() << "Page loaded, status" << loadSuccessful;
	this -> pageReady = loadSuccessful;
}

void KeyEventController::startKeyEventService()
{
	qInfo() << "Key Event service started.";
}
