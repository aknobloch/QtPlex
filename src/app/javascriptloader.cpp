#include "../../include/javascriptloader.h"
#include <QCoreApplication>
#include <QString>
#include <QKeySequence>
#include <QDebug>
#include <QDir>

QString JavaScriptLoader::loadScript(Qt::Key keycode)
{
	QFile jsFunction;

	switch(keycode)
	{
		case Qt::Key_MediaStop :
		{
            jsFunction.setFileName(QCoreApplication::applicationDirPath() + "/js/executeStop.js");
			break;
		}
		case Qt::Key_MediaPrevious :
		{
            jsFunction.setFileName(QCoreApplication::applicationDirPath() + "/js/executePrevious.js");
			break;
		}
		case Qt::Key_MediaPlay :
		{
            jsFunction.setFileName(QCoreApplication::applicationDirPath() + "/js/executePlayPause.js");
			break;
		}
		case Qt::Key_MediaNext :
		{
            jsFunction.setFileName(QCoreApplication::applicationDirPath() + "/js/executeForward.js");
			break;
		}
		default :
		{
			qInfo() << "Invalid key execution, " << QKeySequence(keycode).toString() <<  " not recognized.";
			return "";
		}
	}

	jsFunction.open(QIODevice::ReadOnly);
	QString scriptContents = jsFunction.readAll();

	jsFunction.close();
	return scriptContents;
}
