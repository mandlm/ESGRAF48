#include "GenusWidget.h"
#include "ui_GenusWidget.h"

GenusWidget::GenusWidget(QWidget *parent)
	: QWidget(parent)
	, ui(new Ui::GenusWidget)
{
	ui->setupUi(this);
}

GenusWidget::~GenusWidget()
{
	delete ui;
}
