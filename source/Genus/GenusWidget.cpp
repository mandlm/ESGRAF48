#include "GenusWidget.h"
#include "ui_GenusWidget.h"

#include "GenusModel.h"

GenusWidget::GenusWidget(QWidget *parent)
	: QWidget(parent)
	, ui(new Ui::GenusWidget)
{
	ui->setupUi(this);

    ui->genusTableView->horizontalHeader()->hide();
}

GenusWidget::~GenusWidget()
{
    delete ui;
}

void GenusWidget::setModel(GenusModel *model)
{
    ui->genusTableView->setModel(model);
}
