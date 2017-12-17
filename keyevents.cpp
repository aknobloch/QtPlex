#include <keyevents.h>
#include <mediakeys.h>
#include <QDebug>
#include <QObject>
#include <QThread>

void KeyEventThread::run()
{
	qDebug() << "Key event service started!";

	Key result("Dummy Key", 1);

	emit resultReady(result);
}

void KeyEventController::handleResults(const Key &keyPressed)
{
	qDebug() << "Event " << keyPressed.getName() << " registered.";
}

void KeyEventController::startKeyEventService()
{
	qDebug() << "Starting key event service...";
	KeyEventThread *eventThread = new KeyEventThread();
	connect(eventThread, &KeyEventThread::resultReady, this, &KeyEventController::handleResults);
	connect(eventThread, &KeyEventThread::finished, eventThread, &QObject::deleteLater);
	eventThread -> start();
}
