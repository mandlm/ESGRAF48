#include "mainwindow.h"
#include <QApplication>
#include <QCommandLineParser>

int main(int argc, char **argv)
{
	QApplication app(argc, argv);
	QCoreApplication::setApplicationName("ESGRAF 4-8");
	QCoreApplication::setApplicationVersion("0.1");

	QCommandLineParser cmdParser;
	cmdParser.setApplicationDescription("ESGRAF 4-8");
	cmdParser.addHelpOption();
	cmdParser.addVersionOption();
	cmdParser.addPositionalArgument("filename", "file to open");

	cmdParser.process(app);

	const QStringList args = cmdParser.positionalArguments();

	std::unique_ptr<MainWindow> mainWindow;
	if (args.empty())
	{
		mainWindow = std::make_unique<MainWindow>(nullptr);
	}
	else
	{
		mainWindow = std::make_unique<MainWindow>(nullptr, args.at(0));
	}

	mainWindow->show();

	return app.exec();
}
