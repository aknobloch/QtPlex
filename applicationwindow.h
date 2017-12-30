#ifndef APPLICATIONWINDOW_H
#define APPLICATIONWINDOW_H

#include <QMainWindow>
#include "keyevents.h"

class ApplicationWindow : public QMainWindow
{
		Q_OBJECT

	public:
		ApplicationWindow(QWidget *parent = nullptr);
		void show();

	private:
		KeyEventController *shortcutController;

		void initializeCentralWidget();
		void setHelpWindow();
		void setPlexView(QString serverAddress);
		bool showingHelpScreen();

	signals:

	public slots:
		void showOptionsDialog();
};

#endif // APPLICATIONWINDOW_H
