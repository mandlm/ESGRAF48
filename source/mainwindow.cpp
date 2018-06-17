#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "DataModel.h"

#include <QJsonObject>
#include <QJsonDocument>
#include <QFile>
#include <QFileDialog>
#include <QDataWidgetMapper>

MainWindow::MainWindow(QWidget *parent)
	: QMainWindow(parent)
	, ui(new Ui::MainWindow)
{
	ui->setupUi(this);

	connect(ui->actionNew, SIGNAL(triggered()), this, SLOT(newFile()));
	connect(ui->actionOpen, SIGNAL(triggered()), this, SLOT(openFile()));
    connect(ui->actionSave, SIGNAL(triggered()), this, SLOT(saveFile()));
    connect(ui->actionSave_as, SIGNAL(triggered()), this, SLOT(saveFileAs()));

	newFile();
}

MainWindow::~MainWindow()
{
	delete ui;
}

void MainWindow::newFile()
{
	m_dataModel = std::make_unique<DataModel>(this);
	ui->metaDataWidget->setModel(&m_dataModel->m_metaData);
	ui->verbEndWidget->setModel(&m_dataModel->m_verbEnd);
    ui->genusWidget->setModel(&m_dataModel->m_genus);
	ui->pluralWidget->setModel(&m_dataModel->m_plural);
	ui->akkusativDativWidget->setAkkusativModel(&m_dataModel->m_akkusativ);
	ui->akkusativDativWidget->setDativModel(&m_dataModel->m_dativ);

	ui->resultWidget->setModel(&m_dataModel->m_results);

    m_filename = "";
}

void MainWindow::openFile()
{
	QString filename = QFileDialog::getOpenFileName(this, "Open file", 
			"", "ESGRAF 4-8 (*.esgraf48)");
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

    m_filename = filename;

    ui->metaDataWidget->toFirst();
}

void MainWindow::saveFile()
{
    if (m_filename.isEmpty())
    {
        saveFileAs();
    }
    else
    {
        saveFile(m_filename);
    }
}

void MainWindow::saveFileAs()
{
	QString filename = QFileDialog::getSaveFileName(this, "Save file", "", 
			"ESGRAF 4-8 (*.esgraf48)");
	if (filename.isEmpty())
	{
		return;
	}

    saveFile(filename);
}

void MainWindow::saveFile(const QString &filename)
{
    QJsonObject saveData;
    m_dataModel->write(saveData);

    QJsonDocument saveDoc(saveData);

    QFile saveFile(filename);
    saveFile.open(QFile::WriteOnly);
    saveFile.write(saveDoc.toJson());
    saveFile.close();

    m_filename = filename;
}
