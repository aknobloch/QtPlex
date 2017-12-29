#ifndef HELPWIDGET_H
#define HELPWIDGET_H

#include <QWidget>
#include <QLabel>
#include <QPushButton>

class ConfigServerHelpScreen : public QWidget
{
		Q_OBJECT
	public:
		explicit ConfigServerHelpScreen(QWidget *parent = nullptr);

	private:
		void initializeLayout();
		QLabel * createBanner();
		QLabel * createInfoLabel();
		QPushButton* createConfigButton();

	signals:
		void notifyConfigButtonPressed();

	public slots:
		void configButtonPressed();
};

#endif // HELPWIDGET_H
