#ifndef KEYEVENTTHREAD_H
#define KEYEVENTTHREAD_H

#include <QtWebEngine/QtWebEngine>
#include <QWebEngineView>
#include <QObject>

class KeyEventController : public QObject
{
	Q_OBJECT

	private:
        QWebEnginePage *plexWebPage;
		int pageReady;

	public:
        KeyEventController(QWebEnginePage *view);
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
