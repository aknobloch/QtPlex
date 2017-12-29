#ifndef OPTIONSDIALOG_H
#define OPTIONSDIALOG_H

#include <QDialog>
#include <QLineEdit>
#include <QFormLayout>

class OptionsDialog : public QDialog
{
		Q_OBJECT

	public:
		OptionsDialog();
		void initializeLayout();

	private:
		QLineEdit *serverAddress;

		QFormLayout * createServerInfoForm();

	public slots:
		void okPressed();
};

#endif // OPTIONSDIALOG_H
