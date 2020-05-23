#include "include/javascript_loader.h"

#include <QCoreApplication>
#include <QDebug>
#include <QDir>
#include <QKeySequence>
#include <QString>

QString JavaScriptLoader::loadScriptByName(QString filename) {
  QFile js_file;
  js_file.setFileName(QCoreApplication::applicationDirPath() + "/js/" +
                      filename);
  js_file.open(QIODevice::ReadOnly);

  QString javascript = js_file.readAll();
  js_file.close();

  return javascript;
}
