#include "mainwindow.h"
#include <QApplication>

int main(int argc, char **argv)
{
	QApplication app(argc, argv);

	std::unique_ptr<MainWindow> mainWindow;
	if (argc < 2)
	{
		mainWindow = std::make_unique<MainWindow>(nullptr);
	}
	else
	{
		mainWindow = std::make_unique<MainWindow>(nullptr, argv[1]);
	}

	mainWindow->show();

	return app.exec();
}
