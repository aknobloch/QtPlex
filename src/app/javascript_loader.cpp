#include "../../include/javascript_loader.h"
#include <QCoreApplication>
#include <QString>
#include <QKeySequence>
#include <QDebug>
#include <QDir>

QString JavaScriptLoader::loadScriptByName(QString filename)
{
    QFile jsFunction;
    jsFunction.setFileName(QCoreApplication::applicationDirPath() + "/js/" + filename);

    jsFunction.open(QIODevice::ReadOnly);
    QString scriptContents = jsFunction.readAll();

    jsFunction.close();
    return scriptContents;
}
