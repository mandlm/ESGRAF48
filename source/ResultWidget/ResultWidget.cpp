#include "ResultWidget.h"
#include "ui_ResultWidget.h"

#include "ResultModel.h"

ResultWidget::ResultWidget(QWidget* parent)
    : QWidget(parent)
    , ui(new Ui::ResultWidget)
{
    ui->setupUi(this);
}

ResultWidget::~ResultWidget()
{
    delete ui;
}

void ResultWidget::setModel(ResultModel* model)
{
    ui->resultTableView->setModel(model);
}
