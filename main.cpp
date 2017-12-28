#include <Qt>
#include <QtWebEngine/QtWebEngine>
#include <QApplication>
#include <QWebEngineView>
#include <QInputDialog>
#include <keyevents.h>
#include <optionsdialog.h>

#include <QDebug>

using namespace std;

int main(int argc, char *argv[])
{
	QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
	QCoreApplication::setAttribute(Qt::AA_UseHighDpiPixmaps);

	QApplication app(argc, argv);

	OptionsDialog options;
	options.exec();

	QWebEngineView *view = new QWebEngineView();
	view -> setUrl(QUrl("http://192.168.1.100:32400/web"));

	KeyEventController runner(view);

	view -> showMaximized();
	return app.exec();
}
