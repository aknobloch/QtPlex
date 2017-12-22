#include "javascriptloader.h"
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
			jsFunction.setFileName("executeStop.js");
			break;
		}
		case Qt::Key_MediaPrevious :
		{
			jsFunction.setFileName("executePrevious.js");
			break;
		}
		case Qt::Key_MediaPlay :
		{
			jsFunction.setFileName("executePlayPause.js");
			break;
		}
		case Qt::Key_MediaNext :
		{
			jsFunction.setFileName("executeForward.js");
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
