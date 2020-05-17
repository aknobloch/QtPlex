#ifndef APPLICATIONWINDOW_H
#define APPLICATIONWINDOW_H

#include <QMainWindow>
#include "key_events.h"

class ApplicationWindow : public QMainWindow
{
		Q_OBJECT

	public:
		ApplicationWindow(QWidget *parent = nullptr);
		void show();

	private:
		KeyEventController *shortcutController;

		void initializeMenuBar();
		void initializeCentralWidget();
		void setHelpWindow();
		void setPlexView(QString serverAddress);
		bool showingHelpScreen();

	signals:

	public slots:
		void showSettingsDialog();
};

#endif // APPLICATIONWINDOW_H
