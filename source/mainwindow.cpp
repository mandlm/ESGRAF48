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
	: QMainWindow(parent), ui(new Ui::MainWindow),
	  m_dataModel(new DataModel(parent))
	  , m_widgetMapper(new QDataWidgetMapper(parent))
{
	ui->setupUi(this);

	ui->actionSave_as->setIcon(QIcon::fromTheme("document-save-as", QIcon("/usr/share/gtk-doc/html/gtk2/document-save-as.png")));
	ui->actionLoad->setIcon(QIcon::fromTheme("document-open", QIcon("/usr/share/gtk-doc/html/gtk2/document-open.png")));

	connect(ui->actionSave_as, SIGNAL(triggered()), this, SLOT(saveAs()));
	connect(ui->actionLoad, SIGNAL(triggered()), this, SLOT(load()));

	m_widgetMapper->setModel(&m_dataModel->m_metaData);
	m_widgetMapper->addMapping(ui->lineEdit, 0);
	m_widgetMapper->addMapping(ui->lineEdit_2, 1);
	m_widgetMapper->addMapping(ui->calendarWidget, 2);
	m_widgetMapper->addMapping(ui->calendarWidget_2, 3);
	m_widgetMapper->addMapping(ui->textEdit, 4);
	m_widgetMapper->toFirst();
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

	m_widgetMapper->toFirst();
}
