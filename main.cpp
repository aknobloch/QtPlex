#include <Qt>
#include <QtWebEngine/QtWebEngine>
#include <QApplication>
#include <QWebEngineView>
#include <QInputDialog>
#include <keyevents.h>
#include <optionsdialog.h>
#include <constants.h>

#include <QDebug>

using namespace std;

int main(int argc, char *argv[])
{
	QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
	QCoreApplication::setAttribute(Qt::AA_UseHighDpiPixmaps);

	QCoreApplication::setOrganizationName(ORG_NAME);
	QCoreApplication::setApplicationName(APP_NAME);

	QApplication app(argc, argv);

	QSettings settings;
	QString serverAddress = settings.value(SERVER_ADDRESS_KEY).toString();

	// If server address setting has not yet been defined
	if(serverAddress == 0)
	{
		OptionsDialog options;
		int result = options.exec();

		if(result == QDialog::Rejected)
		{
			return 0;
		}

		serverAddress = settings.value(SERVER_ADDRESS_KEY).toString();
	}

	QWebEngineView *view = new QWebEngineView();
	view -> setUrl(QUrl(serverAddress));

	KeyEventController runner(view);

	view -> showMaximized();
	return app.exec();
}
