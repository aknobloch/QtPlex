#include <Qt>
#include <QtWebEngine/QtWebEngine>
#include <QWebEngineView>
#include <QInputDialog>
#include "keyevents.h"
#include "optionsdialog.h"
#include "constants.h"
#include "applicationwindow.h"
#include "configserverhelp.h"

ApplicationWindow::ApplicationWindow(QWidget *parent) : QMainWindow(parent)
{
	initializeCentralWidget();
	setStyleSheet("background-color:rgb(31,31,31)");
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
		setWindowState(Qt::WindowMaximized);
		setPlexView(serverAddress);
	}
}

void ApplicationWindow::setHelpWindow()
{
	ConfigServerHelpScreen *help = new ConfigServerHelpScreen();
	connect(help, &ConfigServerHelpScreen::notifyConfigButtonPressed, this, &ApplicationWindow::showOptionsDialog);

	setCentralWidget(help);
}

void ApplicationWindow::setPlexView(QString serverAddress)
{
	QWebEngineView *view = new QWebEngineView();
	view -> setUrl(QUrl(serverAddress));

	shortcutController = new KeyEventController(view);

	setCentralWidget(view);
}

void ApplicationWindow::show()
{
	if(showingHelpScreen())
	{
		showNormal();
	}
	else
	{
		showMaximized();
	}
}

void ApplicationWindow::showOptionsDialog()
{
	OptionsDialog options;
	int result = options.exec();

	initializeCentralWidget();
}

bool ApplicationWindow::showingHelpScreen()
{
	if(ConfigServerHelpScreen *test = dynamic_cast<ConfigServerHelpScreen*>(centralWidget()))
	{
		return true;
	}

	return false;
}
