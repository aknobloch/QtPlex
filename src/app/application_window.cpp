#include <Qt>
#include <QtWebEngine/QtWebEngine>
#include <QWebEngineView>
#include <QInputDialog>
#include <QDesktopWidget>
#include <QMenuBar>
#include "../../include/key_events.h"
#include "../../include/settings_dialog.h"
#include "../../include/constants.h"
#include "../../include/application_window.h"
#include "../../include/config_server_help.h"
#include "../../include/plex_web_page.h"

ApplicationWindow::ApplicationWindow(QWidget *parent) : QMainWindow(parent)
{
    resize(QDesktopWidget().availableGeometry(this).size() * 0.7);
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
    PlexWebPage *page = new PlexWebPage();
    page->setUrl(QUrl(serverAddress));

    QWebEngineView *view = new QWebEngineView();
    view->setPage(page);
    view->show();

    shortcutController = new KeyEventController(page);
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
	QSettings settings;
	QString oldServerAddress = settings.value(SERVER_ADDRESS_KEY).toString();

	SettingsDialog options;
	options.exec();

	QString newServerAddress = settings.value(SERVER_ADDRESS_KEY).toString();
	bool changedServerAdddress = oldServerAddress.compare(newServerAddress) != 0;

	if(showingHelpScreen() || changedServerAdddress)
	{
		initializeCentralWidget();
	}
}

bool ApplicationWindow::showingHelpScreen()
{
	if(dynamic_cast<ConfigServerHelpScreen*>(centralWidget()))
	{
		return true;
	}

	return false;
}
