#include <QApplication>
#include <QDebug>
#include <Qt>

#include "application_window.h"
#include "constants.h"

using namespace std;

int main(int argc, char *argv[]) {
  QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
  QCoreApplication::setAttribute(Qt::AA_UseHighDpiPixmaps);

  QCoreApplication::setOrganizationName(kOrganizationName);
  QCoreApplication::setApplicationName(kAppName);

  QApplication app(argc, argv);

  ApplicationWindow window;
  window.show();

  return app.exec();
}
