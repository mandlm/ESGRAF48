#include "MetaDataWidget.h"
#include "ui_MetaDataWidget.h"

MetaDataWidget::MetaDataWidget(QWidget *parent)
	: QWidget(parent), ui(new Ui::MetaDataWidget)
{
	ui->setupUi(this);
}

MetaDataWidget::~MetaDataWidget()
{
	delete ui;
}

