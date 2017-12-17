
#include <QtWebEngine/QtWebEngine>
#include <QWebEngineView>
#include <QObject>
#include <QThread>
#include <QDebug>
#include <keyevents.h>
#include <mediakeys.h>

void KeyEventThread::run()
{
	qInfo() << "Key event service started!";

	Display*    dpy     = XOpenDisplay(0);
	Window      root    = DefaultRootWindow(dpy);
	XEvent      event;

	// initial grab for media keys
	grabKeys(dpy, root);

	// TODO destructor boolean control
	while(true)
	{
		XNextEvent(dpy, &event);

		switch(event.type)
		{
			case KeyPress:

				Key pressed_key = keyManager.getKey(event.xkey.keycode);
				emit notifyKeyPressed(pressed_key);
		}
	}
}

void KeyEventThread::grabKeys(Display *display, Window &grab_window)
{
	unsigned int    modifiers       = AnyModifier;
	Bool            owner_events    = False;
	int             pointer_mode    = GrabModeAsync;
	int             keyboard_mode   = GrabModeAsync;

	vector<Key> keys = keyManager.getMediaKeys();

	for(vector<Key>::iterator it = keys.begin(); it < keys.end(); it++)
	{
		Key next_key = *it;
		XGrabKey(display, next_key.getKeyCode(), modifiers, grab_window, owner_events, pointer_mode, keyboard_mode);
	}
}

KeyEventController::KeyEventController(QWebEngineView *view)
{
	this -> plexWebView = view;
	this -> pageReady = 0;
	connect(plexWebView, &QWebEngineView::loadFinished, this, &KeyEventController::pageLoaded);
}

void KeyEventController::pageLoaded(int loadSuccessful)
{
	qInfo() << "Page loaded, status" << loadSuccessful;
	this -> pageReady = loadSuccessful;
}

void KeyEventController::handleKeyPressed(const Key &keyPressed)
{
	qInfo() << "Event " << keyPressed.getName() << " registered.";

	if(this -> pageReady != 1)
	{
		qInfo() << "Page not loaded, ignoring key press.";
		return;
	}

	switch(keyPressed.getKeyCode())
	{
		case MediaKeyCodes::STOP :
		{
			QString pressForward = "document.getElementsByClassName(\"stop-btn\")[0].click()";
			plexWebView -> page() -> runJavaScript(pressForward);
			break;
		}
			break;
		case MediaKeyCodes::BACK :
		{
			QString pressForward = "document.getElementsByClassName(\"previous-btn\")[0].click()";
			plexWebView -> page() -> runJavaScript(pressForward);
			break;
		}
			break;
		case MediaKeyCodes::PLAY_PAUSE :
		{
			QString pressForward = "document.getElementsByClassName(\"play-btn\")[0].click()";
			plexWebView -> page() -> runJavaScript(pressForward);
			break;
		}
			break;
		case MediaKeyCodes::FORWARD :
		{
			QString pressForward = "document.getElementsByClassName(\"next-btn\")[0].click()";
			plexWebView -> page() -> runJavaScript(pressForward);
			break;
		}
		default:
		{
			qDebug() << "Media key code not recognized.";
		}
	}
}

Q_DECLARE_METATYPE(Key)
void KeyEventController::startKeyEventService()
{
	qRegisterMetaType<Key>();

	qDebug() << "Starting key event service...";
	KeyEventThread *eventThread = new KeyEventThread();
	connect(eventThread, &KeyEventThread::notifyKeyPressed, this, &KeyEventController::handleKeyPressed);
	connect(eventThread, &KeyEventThread::finished, eventThread, &QObject::deleteLater);
	eventThread -> start();
}
