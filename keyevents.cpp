#include "keyevents.h"
#include <QDebug>
#include <QObject>
#include <QThread>

void KeyEventThread::run()
{
	qDebug() << "Key event service started!";

	QString result = "done.";

	emit resultReady(result);
}

void KeyEventController::handleResults(const QString &s)
{
	qDebug() << "Event " << s << " registered.";
}

void KeyEventController::startKeyEventService()
{
	qDebug() << "Starting key event service...";
	KeyEventThread *eventThread = new KeyEventThread();
	connect(eventThread, &KeyEventThread::resultReady, this, &KeyEventController::handleResults);
	connect(eventThread, &KeyEventThread::finished, eventThread, &QObject::deleteLater);
	eventThread -> start();
}
