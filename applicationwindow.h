#ifndef APPLICATIONWINDOW_H
#define APPLICATIONWINDOW_H

#include <QMainWindow>

class ApplicationWindow : public QMainWindow
{
		Q_OBJECT
	public:
		ApplicationWindow(QWidget *parent = nullptr);
		void show();

	private:
		void initializeCentralWidget();
		void setHelpWindow();
		void setPlexView(QString serverAddress);
		bool showingHelpScreen();

	signals:

	public slots:
		void showOptionsDialog();
};

#endif // APPLICATIONWINDOW_H
