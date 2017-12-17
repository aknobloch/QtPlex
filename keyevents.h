#ifndef KEYEVENTTHREAD_H
#define KEYEVENTTHREAD_H

#include <QThread>
#include <QObject>

class KeyEventThread : public QThread
{
	Q_OBJECT

	public:
		void run() override;

	signals:
		void resultReady(const QString &s);
};

class KeyEventController : public QObject
{
	Q_OBJECT

	public:
		void startKeyEventService();

	public slots:
		void handleResults(const QString &s);
};

#endif // KEYEVENTTHREAD_H
