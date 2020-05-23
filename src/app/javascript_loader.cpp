#include "include/javascript_loader.h"

#include <QCoreApplication>
#include <QDebug>
#include <QDir>
#include <QKeySequence>
#include <QString>

QString JavaScriptLoader::loadScriptByName(QString filename) {
  QFile jsFile;
  jsFile.setFileName(QCoreApplication::applicationDirPath() + "/js/" +
                     filename);
  jsFile.open(QIODevice::ReadOnly);

  QString javascript = jsFile.readAll();
  jsFile.close();

  return javascript;
}
