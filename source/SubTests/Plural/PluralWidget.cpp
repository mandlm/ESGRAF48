#include "PluralWidget.h"
#include "ui_PluralWidget.h"

#include "PluralModel.h"

PluralWidget::PluralWidget(QWidget *parent)
	: QWidget(parent)
	, ui(new Ui::PluralWidget)
{
	ui->setupUi(this);
}

PluralWidget::~PluralWidget()
{
	delete ui;
}

void PluralWidget::setModel(PluralModel *model)
{
	ui->pluralTableView->setModel(model);
    ui->pluralTableView->resizeColumnsToContents();
}
