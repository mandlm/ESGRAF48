#include "V2SvkWidget.h"
#include "ui_V2SvkWidget.h"

#include "V2SvkModel.h"

V2SvkWidget::V2SvkWidget(QWidget *parent)
	: QWidget(parent)
	, ui(new Ui::V2SvkWidget)
{
	ui->setupUi(this);
    ui->v2SvkTableView->horizontalHeader()->hide();
}

V2SvkWidget::~V2SvkWidget()
{
	delete ui;
}

void V2SvkWidget::setV2SvkModel(V2SvkModel *model)
{
	ui->v2SvkTableView->setModel(model);
}
