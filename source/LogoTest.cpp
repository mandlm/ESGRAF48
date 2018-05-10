#include "mainwindow.h"
#include <QApplication>

#include "testdata.h"
#include <QJsonObject>
#include <QJsonDocument>
#include <QFile>

int main(int argc, char **argv)
{
	TestData testData;
	QJsonObject saveData;
	testData.write(saveData);

	QJsonDocument saveDoc(saveData);

	QFile saveFile("testdata.json");
	saveFile.open(QFile::WriteOnly);
	saveFile.write(saveDoc.toJson());
	saveFile.close();

	QApplication app(argc, argv);
	MainWindow mainWindow;
	mainWindow.show();

	return app.exec();
}
