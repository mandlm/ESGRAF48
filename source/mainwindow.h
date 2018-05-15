#pragma once

#include <QMainWindow>

namespace Ui {
class MainWindow;
};

class MainWindow : public QMainWindow
{
	Q_OBJECT

public:
	MainWindow(QWidget *parent = nullptr);
	~MainWindow();

public slots:
	void saveAs();

private:
	Ui::MainWindow *ui;
};
