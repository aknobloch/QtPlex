#ifndef KEYEVENTTHREAD_H
#define KEYEVENTTHREAD_H

#include <QThread>
#include <QObject>
#include <mediakeys.h>

class KeyEventThread : public QThread
{
	Q_OBJECT

	public:
		void run() override;

	signals:
		void resultReady(const Key &keyPressed);
};

class KeyEventController : public QObject
{
	Q_OBJECT

	public:
		void startKeyEventService();

	public slots:
		void handleResults(const Key &keyPressed);
};

#endif // KEYEVENTTHREAD_H
