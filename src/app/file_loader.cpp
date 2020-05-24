#include "file_loader.h"

#include <QCoreApplication>
#include <QDebug>
#include <QDir>
#include <QKeySequence>
#include <QString>

#include "constants.h"

namespace {
QString readFileByName(QString subdir, QString filename) {
  QFile file;
  file.setFileName(QCoreApplication::applicationDirPath() + subdir + filename);
  file.open(QIODevice::ReadOnly);

  QString contents = file.readAll();
  file.close();

  return contents;
}
}  // namespace

QString FileLoader::loadJavascriptByName(QString filename) {
  return readFileByName(kJavascriptDir, filename);
}

QString FileLoader::loadCSSByName(QString filename) {
  return readFileByName(kCSSDir, filename);
}
