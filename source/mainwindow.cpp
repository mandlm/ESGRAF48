#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "testdata.h"
#include "MetaDataModel.h"
#include <QJsonObject>
#include <QJsonDocument>
#include <QFile>
#include <QFileDialog>
#include <QDataWidgetMapper>


MainWindow::MainWindow(QWidget *parent)
	: QMainWindow(parent), ui(new Ui::MainWindow)
{
	ui->setupUi(this);

	ui->actionSave_as->setIcon(QIcon::fromTheme("document-save-as", QIcon("/usr/share/gtk-doc/html/gtk2/document-save-as.png")));
	connect(ui->actionSave_as, SIGNAL(triggered()), this, SLOT(saveAs()));

	MetaDataModel *metaDataModel = new MetaDataModel(this);

	QDataWidgetMapper *mapper = new QDataWidgetMapper(this);
	mapper->setModel(metaDataModel);
	mapper->addMapping(ui->lineEdit, 0);
	mapper->addMapping(ui->lineEdit_2, 1);
	mapper->addMapping(ui->calendarWidget, 2);
	mapper->addMapping(ui->calendarWidget_2, 3);
	mapper->addMapping(ui->textEdit, 4);
	mapper->toFirst();

	//ui->tableView->setModel(metaDataModel);
}

MainWindow::~MainWindow()
{
	delete ui;
}

void MainWindow::saveAs()
{
	QString filename = QFileDialog::getSaveFileName(this);
	if (filename.isEmpty())
	{
		return;
	}

	TestData testData;
	QJsonObject saveData;
	testData.write(saveData);

	QJsonDocument saveDoc(saveData);

	QFile saveFile(filename);
	saveFile.open(QFile::WriteOnly);
	saveFile.write(saveDoc.toJson());
	saveFile.close();
}
