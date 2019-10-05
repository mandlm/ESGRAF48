#include "PluralWidget.h"
#include "ui_PluralWidget.h"

#include "PluralModel.h"

PluralWidget::PluralWidget(QWidget* parent)
    : QWidget(parent)
    , ui(new Ui::PluralWidget)
{
    ui->setupUi(this);

    ui->pluralTableView->horizontalHeader()->hide();
}

PluralWidget::~PluralWidget()
{
    delete ui;
}

void PluralWidget::setModel(PluralModel* model)
{
    ui->pluralTableView->setModel(model);
}
