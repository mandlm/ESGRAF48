#include "V2SvkWidget.h"
#include "ui_V2SvkWidget.h"

#include "WFModel.h"
#include "OTModel.h"
#include "TPrModel.h"
#include "TPeModel.h"

V2SvkWidget::V2SvkWidget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::V2SvkWidget)
{
	ui->setupUi(this);
	ui->wfTableView->horizontalHeader()->hide();
	ui->otTableView->horizontalHeader()->hide();
	ui->tprTableView->horizontalHeader()->hide();
	ui->tpeTableView->horizontalHeader()->hide();
}

V2SvkWidget::~V2SvkWidget()
{
	delete ui;
}

void V2SvkWidget::setWFModel(WFModel *model)
{
	ui->wfTableView->setModel(model);
}

void V2SvkWidget::setOTModel(OTModel *model)
{
	ui->otTableView->setModel(model);
}

void V2SvkWidget::setTPrModel(TPrModel *model)
{
	ui->tprTableView->setModel(model);
}

void V2SvkWidget::setTPeModel(TPeModel *model)
{
	ui->tpeTableView->setModel(model);
}
