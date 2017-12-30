#include <Qt>
#include <QtWebEngine/QtWebEngine>
#include <QWebEngineView>
#include <QInputDialog>
#include <QMenuBar>
#include "keyevents.h"
#include "settingsdialog.h"
#include "constants.h"
#include "applicationwindow.h"
#include "configserverhelp.h"

ApplicationWindow::ApplicationWindow(QWidget *parent) : QMainWindow(parent)
{
	initializeMenuBar();
	initializeCentralWidget();
	setStyleSheet("background-color:rgb(31,31,31)");
}

void ApplicationWindow::initializeMenuBar()
{
	QMenu *file = new QMenu("File");
	file -> addAction("Settings", this, &ApplicationWindow::showSettingsDialog);

	menuBar() -> setStyleSheet("background-color:rgb(244,244,244)");
	menuBar() -> addMenu(file);
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
	connect(help, &ConfigServerHelpScreen::notifyConfigButtonPressed, this, &ApplicationWindow::showSettingsDialog);

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

void ApplicationWindow::showSettingsDialog()
{
	SettingsDialog options;
	int result = options.exec();

	if(showingHelpScreen())
	{
		initializeCentralWidget();
	}
}

bool ApplicationWindow::showingHelpScreen()
{
	if(ConfigServerHelpScreen *test = dynamic_cast<ConfigServerHelpScreen*>(centralWidget()))
	{
		return true;
	}

	return false;
}
