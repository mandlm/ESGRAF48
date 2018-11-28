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

#include <fstream>

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

	std::fstream protoInFile(filename.toStdString(), std::ios::in | std::ios::binary);
	m_dataModel->read(protoInFile);

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
	QFileDialog saveFilenameDialog(this);
	saveFilenameDialog.setDefaultSuffix("esgraf48");
	saveFilenameDialog.setFileMode(QFileDialog::AnyFile);
	saveFilenameDialog.setNameFilter("ESGRAF 4-8 (*.esgraf48)");
	saveFilenameDialog.setWindowTitle("Save file");

	if (!saveFilenameDialog.exec())
	{
		return;
	}

	saveFile(saveFilenameDialog.selectedFiles().first());
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
	QTextCursor printCursor(&printDoc);
	m_dataModel->printTo(printCursor);

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
	std::fstream protoOutFile(filename.toStdString(),
	                          std::ios::out | std::ios::trunc | std::ios::binary);
	m_dataModel->write(protoOutFile);

	qDebug() << "Wrote" << filename;

	setWindowTitle(filename + "[*]");
	setWindowModified(false);
	m_filename = filename;
	m_saveOnClose = false;
}
