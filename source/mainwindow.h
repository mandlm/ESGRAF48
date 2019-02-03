#pragma once

#include "DataModel.h"

#include <QMainWindow>
#include <QString>
#include <QFont>


class DataModel;
class QDataWidgetMapper;

namespace Ui {
class MainWindow;
};

class MainWindow : public QMainWindow
{
	Q_OBJECT

private:
	Ui::MainWindow *ui;
	DataModel m_dataModel;
	QString m_filename;
	bool m_saveOnClose = false;

public:
	MainWindow(QWidget *parent);
	MainWindow(QWidget *parent, const QString &filename);
	~MainWindow();

public slots:
	void newFile();
	void openFile();
	void openFile(const QString &filename);
	void saveFile();
	void saveFileAs();
	void closeFile();
	void print() const;
	void dataModelChanged();
	void savePdf();
	void aboutDialog();

protected:
	void closeEvent(QCloseEvent *event) override;

private:
	void setupUi();
	void saveFile(const QString &filename);
	void savePdf(const QString &filename);
};
