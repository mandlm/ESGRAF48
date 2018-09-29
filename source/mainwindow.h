#pragma once

#include <QMainWindow>

#include <memory>

class DataModel;
class QDataWidgetMapper;

namespace Ui {
class MainWindow;
};

class MainWindow : public QMainWindow
{
	Q_OBJECT

private:
	Ui::MainWindow *ui;
	std::unique_ptr<DataModel> m_dataModel;
    QString m_filename;
	bool m_saveOnClose = false;

public:
	MainWindow(QWidget *parent = nullptr);
	~MainWindow();

public slots:
	void newFile();
	void openFile();
    void saveFile();
	void saveFileAs();
	void dataModelChanged();

protected:
	void closeEvent(QCloseEvent *event) override;

private:
    void saveFile(const QString &filename);
};
