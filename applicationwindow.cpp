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
	QSettings settings;
	QString serverAddress = settings.value(SERVER_ADDRESS_KEY).toString();

	// If server address setting has not yet been defined
	if(serverAddress == 0)
	{
		OptionsDialog options;
		int result = options.exec();

		if(result == QDialog::Rejected)
		{
			serverAddress = QString(); // null string
		}
		else
		{
			serverAddress = settings.value(SERVER_ADDRESS_KEY).toString();
		}
	}

	if(serverAddress.isNull())
	{
		throw;
	}

	QWebEngineView *view = new QWebEngineView();
	view -> setUrl(QUrl(serverAddress));

	KeyEventController runner(view);

	setCentralWidget(view);
}
