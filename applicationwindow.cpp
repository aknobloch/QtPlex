#include <Qt>
#include <QtWebEngine/QtWebEngine>
#include <QWebEngineView>
#include <QInputDialog>
#include "keyevents.h"
#include "optionsdialog.h"
#include "constants.h"
#include "applicationwindow.h"

ApplicationWindow::ApplicationWindow(QWidget *parent) : QMainWindow(parent)
{
	initializeCentralWidget();
}


void ApplicationWindow::initializeCentralWidget()
{
	QSettings settings;
	QString serverAddress = settings.value(SERVER_ADDRESS_KEY).toString();

	// If server address setting has not yet been defined
	if(serverAddress.isNull())
	{
		setHelpWindow();
	}
	else
	{
		setPlexView(serverAddress);
	}
}

void ApplicationWindow::setHelpWindow()
{
	OptionsDialog options;
	int result = options.exec();
}

void ApplicationWindow::setPlexView(QString serverAddress)
{
	QWebEngineView *view = new QWebEngineView();
	view -> setUrl(QUrl(serverAddress));

	KeyEventController runner(view);

	setCentralWidget(view);
}
