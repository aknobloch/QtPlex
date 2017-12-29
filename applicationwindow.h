#ifndef APPLICATIONWINDOW_H
#define APPLICATIONWINDOW_H

#include <QMainWindow>

class ApplicationWindow : public QMainWindow
{
		Q_OBJECT
	public:
		ApplicationWindow(QWidget *parent = nullptr);

	private:
		void initializeCentralWidget();
		void setHelpWindow();
		void setPlexView(QString serverAddress);

	signals:

	public slots:
};

#endif // APPLICATIONWINDOW_H
