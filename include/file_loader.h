#ifndef FILELOADER_H
#define FILELOADER_H

#include <QFile>

class FileLoader {
 public:
  static QString loadJavascriptByName(QString filename);
  static QString loadCSSByName(QString filename);
};

#endif  // FILELOADER_H
