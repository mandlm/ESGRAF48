#include "mainwindow.h"

#include "version.h"

#include <QApplication>
#include <QCommandLineParser>

int main(int argc, char** argv)
{
    QApplication app(argc, argv);
    QCoreApplication::setApplicationName(ESGRAF48_DESCRIPTION);
    QCoreApplication::setApplicationVersion(ESGRAF48_VERSION);

    QCommandLineParser cmdParser;
    cmdParser.setApplicationDescription(ESGRAF48_DESCRIPTION);
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
