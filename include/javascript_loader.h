#ifndef JAVASCRIPTLOADER_H
#define JAVASCRIPTLOADER_H

#include <QFile>

class JavaScriptLoader
{
	public:
        static QString loadScriptByKeycode(Qt::Key keycode);
        static QString loadScriptByName(QString filename);
};

#endif // JAVASCRIPTLOADER_H
