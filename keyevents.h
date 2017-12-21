#ifndef KEYEVENTTHREAD_H
#define KEYEVENTTHREAD_H

#include <QtWebEngine/QtWebEngine>
#include <QWebEngineView>
#include <QObject>
#include <mediakeys.h>

class KeyEventController : public QObject
{
	Q_OBJECT

	private:
		QWebEngineView *plexWebView;
		int pageReady;

	public:
		KeyEventController(QWebEngineView *view);
		void startKeyEventService();

	public slots:
		void pageLoaded(int loadSuccessful);

};

#endif // KEYEVENTTHREAD_H
