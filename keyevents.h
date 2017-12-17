#ifndef KEYEVENTTHREAD_H
#define KEYEVENTTHREAD_H

#include <QThread>
#include <QObject>
#include <QX11Info>
#include <qtextstream.h>
#include <X11/Xlib.h>
#include <mediakeys.h>

class KeyEventThread : public QThread
{
	Q_OBJECT

	private:
		MediaKeys keyManager;

	public:
		void run() override;
		void grabKeys(Display *display, Window &grab_window);

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
