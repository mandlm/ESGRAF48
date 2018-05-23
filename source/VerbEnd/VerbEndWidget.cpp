#include "VerbEndWidget.h"
#include "ui_VerbEndWidget.h"

#include "VerbEndModel.h"

VerbEndWidget::VerbEndWidget(QWidget *parent)
	: QWidget(parent)
	, ui(new Ui::VerbEndWidget)
{
	ui->setupUi(this);

	ui->verbEndTableView->horizontalHeader()->hide();
}

VerbEndWidget::~VerbEndWidget()
{
	delete ui;
}

void VerbEndWidget::setModel(VerbEndModel *model)
{
	ui->verbEndTableView->setModel(model);
}
