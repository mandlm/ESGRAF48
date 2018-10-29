#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "DataModel.h"

#include <QJsonObject>
#include <QJsonDocument>
#include <QFile>
#include <QFileDialog>
#include <QDataWidgetMapper>
#include <QCloseEvent>
#include <QMessageBox>
#include <QtPrintSupport/QPrinter>
#include <QtPrintSupport/QPrintDialog>
#include <QTextDocument>

#include <QDebug>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
	ui->setupUi(this);

	connect(ui->actionNew, &QAction::triggered, this, &MainWindow::newFile);
	connect(ui->actionOpen, &QAction::triggered, this, &MainWindow::openFile);
	connect(ui->actionSave, &QAction::triggered, this, qOverload<>(&MainWindow::saveFile));
	connect(ui->actionSave_as, &QAction::triggered, this, &MainWindow::saveFileAs);
	connect(ui->actionPrint, &QAction::triggered, this, &MainWindow::print);

	newFile();
}

MainWindow::~MainWindow()
{
	delete ui;
}

void MainWindow::newFile()
{
	closeFile();

	m_dataModel = std::make_unique<DataModel>(this);
	ui->metaDataWidget->setModel(&m_dataModel->m_metaData);
	ui->verbEndWidget->setModel(&m_dataModel->m_verbEnd);
	ui->genusWidget->setModel(&m_dataModel->m_genus);
	ui->pluralWidget->setModel(&m_dataModel->m_plural);
	ui->akkusativDativWidget->setAkkusativModel(&m_dataModel->m_akkusativ);
	ui->akkusativDativWidget->setDativModel(&m_dataModel->m_dativ);
	ui->v2SvkWidget->setV2SvkModel(&m_dataModel->m_v2Svk);
	ui->lateSkillsWidget->setPassivModel(&m_dataModel->m_passiv);
	ui->lateSkillsWidget->setGenitivModel(&m_dataModel->m_genitiv);

	ui->resultWidget->setModel(&m_dataModel->m_results);

	connect(&*m_dataModel, &DataModel::modelChanged, this, &MainWindow::dataModelChanged);

	setWindowModified(false);
	setWindowTitle("untitled[*]");
	m_filename = "";
	m_saveOnClose = false;
}

void MainWindow::openFile()
{
	QString filename =
	    QFileDialog::getOpenFileName(this, "Open file", "", "ESGRAF 4-8 (*.esgraf48)");
	if (filename.isEmpty())
	{
		return;
	}

	closeFile();

	QFile loadFile(filename);
	if (!loadFile.open(QFile::ReadOnly))
	{
		qWarning("Could not open file");
		return;
	}

	QByteArray byteData = loadFile.readAll();
	QJsonDocument loadDoc = QJsonDocument::fromJson(byteData);

	m_dataModel->read(loadDoc.object());

	setWindowModified(false);
	setWindowTitle(filename + "[*]");
	m_saveOnClose = false;
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
	QString filename =
	    QFileDialog::getSaveFileName(this, "Save file", "", "ESGRAF 4-8 (*.esgraf48)");
	if (filename.isEmpty())
	{
		return;
	}

	saveFile(filename);
}

void MainWindow::closeFile()
{
	if (m_saveOnClose == true)
	{
		QMessageBox msgBox;
		msgBox.setText("The document has been modified.");
		msgBox.setInformativeText("Do you want to save your changes?");
		msgBox.setStandardButtons(QMessageBox::Save | QMessageBox::Discard);
		msgBox.setDefaultButton(QMessageBox::Save);

		if (msgBox.exec() == QMessageBox::Save)
		{
			saveFile();
		}
	}
}

void MainWindow::print() const
{
	QPrinter printer;

	QPrintDialog dialog(&printer);
	if (dialog.exec() != QDialog::Accepted)
	{
		return;
	}

	QTextDocument printDoc;
	printDoc.setHtml(
	    "<html>"
	    "<body>"
	    "<h2>Hello World</h2>"
	    "</body>"
	    "</hthml>");

	printDoc.print(&printer);
}

void MainWindow::dataModelChanged()
{
	m_saveOnClose = true;
	setWindowModified(true);
}

void MainWindow::closeEvent(QCloseEvent *event)
{
	closeFile();
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

	qDebug() << "Wrote" << filename;

	setWindowTitle(filename + "[*]");
	setWindowModified(false);
	m_filename = filename;
	m_saveOnClose = false;
}
