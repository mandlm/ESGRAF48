#include "AkkusativDativWidget.h"
#include "ui_AkkusativDativWidget.h"

#include "AkkusativModel.h"
#include "DativModel.h"

AkkusativDativWidget::AkkusativDativWidget(QWidget *parent)
	: QWidget(parent)
	, ui(new Ui::AkkusativDativWidget)
{
	ui->setupUi(this);
    ui->akkusativTableView->horizontalHeader()->hide();
    ui->dativTableView->horizontalHeader()->hide();
}

AkkusativDativWidget::~AkkusativDativWidget()
{
	delete ui;
}

void AkkusativDativWidget::setAkkusativModel(AkkusativModel *model)
{
	ui->akkusativTableView->setModel(model);
}
	
void AkkusativDativWidget::setDativModel(DativModel *model)
{
	ui->dativTableView->setModel(model);
}
