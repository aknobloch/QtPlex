#include "../../include/javascript_loader.h"
#include <QCoreApplication>
#include <QDebug>
#include <QDir>
#include <QKeySequence>
#include <QString>

QString JavaScriptLoader::loadScriptByName(QString filename) {
  QFile jsFunction;
  jsFunction.setFileName(QCoreApplication::applicationDirPath() + "/js/" +
                         filename);

  jsFunction.open(QIODevice::ReadOnly);
  QString scriptContents = jsFunction.readAll();

  jsFunction.close();
  return scriptContents;
}
