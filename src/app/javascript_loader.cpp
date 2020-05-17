#include "../../include/javascript_loader.h"
#include <QCoreApplication>
#include <QString>
#include <QKeySequence>
#include <QDebug>
#include <QDir>

<<<<<<< HEAD
=======
QString JavaScriptLoader::loadScriptByKeycode(Qt::Key keycode)
{
	switch(keycode)
	{
		case Qt::Key_MediaStop :
		{
            return loadScriptByName("executeStop.js");
		}
		case Qt::Key_MediaPrevious :
		{
            return loadScriptByName("executePrevious.js");
		}
		case Qt::Key_MediaPlay :
		{
            return loadScriptByName("executePlayPause.js");
		}
		case Qt::Key_MediaNext :
		{
            return loadScriptByName("executeForward.js");
		}
		default :
		{
			qInfo() << "Invalid key execution, " << QKeySequence(keycode).toString() <<  " not recognized.";
			return "";
		}
    }
}

>>>>>>> b67aacebd7353ec510d6a75591d8a53df1bbbcd2
QString JavaScriptLoader::loadScriptByName(QString filename)
{
    QFile jsFunction;
    jsFunction.setFileName(QCoreApplication::applicationDirPath() + "/js/" + filename);

    jsFunction.open(QIODevice::ReadOnly);
    QString scriptContents = jsFunction.readAll();

    jsFunction.close();
    return scriptContents;
}
