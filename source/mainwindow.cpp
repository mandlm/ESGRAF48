#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "DataModel.h"
#include "MetaDataModel.h"

#include <QJsonObject>
#include <QJsonDocument>
#include <QFile>
#include <QFileDialog>
#include <QDataWidgetMapper>

MainWindow::MainWindow(QWidget *parent)
	: QMainWindow(parent)
	, ui(new Ui::MainWindow)
	, m_dataModel(new DataModel(parent))
{
	ui->setupUi(this);

	connect(ui->actionSave_as, SIGNAL(triggered()), this, SLOT(saveAs()));
	connect(ui->actionOpen, SIGNAL(triggered()), this, SLOT(load()));

	ui->metaDataWidget->setModel(&m_dataModel->m_metaData);
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

	QJsonObject saveData;
	m_dataModel->write(saveData);

	QJsonDocument saveDoc(saveData);

	QFile saveFile(filename);
	saveFile.open(QFile::WriteOnly);
	saveFile.write(saveDoc.toJson());
	saveFile.close();
}

void MainWindow::load()
{
	QString filename = QFileDialog::getOpenFileName(this);
	if (filename.isEmpty())
	{
		return;
	}

	QFile loadFile(filename);
	if (!loadFile.open(QFile::ReadOnly))
	{
		qWarning("Could not open file");
		return;
	}

	QByteArray byteData = loadFile.readAll();
	QJsonDocument loadDoc = QJsonDocument::fromJson(byteData);

	m_dataModel->read(loadDoc.object());

	ui->metaDataWidget->toFirst();
}
