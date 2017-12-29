#include <Qt>
#include <QApplication>
#include "constants.h"
#include "applicationwindow.h"

#include <QDebug>

using namespace std;

int main(int argc, char *argv[])
{
	QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
	QCoreApplication::setAttribute(Qt::AA_UseHighDpiPixmaps);

	QCoreApplication::setOrganizationName(ORG_NAME);
	QCoreApplication::setApplicationName(APP_NAME);

	QApplication app(argc, argv);

	ApplicationWindow window;
	window.showMaximized();

	return app.exec();
}
