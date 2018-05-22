#include "GenusWidget.h"
#include "ui_GenusWidget.h"

#include "GenusModel.h"

GenusWidget::GenusWidget(QWidget *parent)
	: QWidget(parent)
	, ui(new Ui::GenusWidget)
	, m_model(new GenusModel(this))
{
	ui->setupUi(this);

	ui->tableView->horizontalHeader()->hide();
	ui->tableView->setModel(m_model);
}

GenusWidget::~GenusWidget()
{
	delete ui;
}
