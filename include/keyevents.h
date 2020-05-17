#ifndef KEYEVENTTHREAD_H
#define KEYEVENTTHREAD_H

#include <QtWebEngine/QtWebEngine>
#include <QWebEngineView>
#include <QObject>
#include "media_status_notification.h"
#include "plex_web_page.h"

class KeyEventController : public QObject
{
	Q_OBJECT

	private:
        PlexWebPage *plexWebPage;
        MediaStatusNotification *statusNotifier;
		int pageReady;

	public:
        KeyEventController(PlexWebPage *view);
        ~KeyEventController();
		void startKeyEventService();

	public slots:
		void pageLoaded(int loadSuccessful);
		void executeKey(Qt::Key keyPressed);
		void stopPressed();
		void prevPressed();
		void playPressed();
		void nextPressed();

};

#endif // KEYEVENTTHREAD_H
