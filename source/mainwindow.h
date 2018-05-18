#pragma once

#include <QMainWindow>

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
	DataModel *m_dataModel;

public:
	MainWindow(QWidget *parent = nullptr);
	~MainWindow();

public slots:
	void saveAs();
	void load();
};
