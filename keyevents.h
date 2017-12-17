#ifndef KEYEVENTTHREAD_H
#define KEYEVENTTHREAD_H

#include <QtWebEngine/QtWebEngine>
#include <QWebEngineView>
#include <QObject>
#include <QThread>
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
		void notifyKeyPressed(const Key &keyPressed);
};

class KeyEventController : public QObject
{
	Q_OBJECT

	private:
		QWebEngineView *plexWebView;

	public:
		KeyEventController(QWebEngineView *view);
		void startKeyEventService();

	public slots:
		void handleKeyPressed(const Key &keyPressed);
		void pageLoaded(int loadSuccessful);
};

#endif // KEYEVENTTHREAD_H
