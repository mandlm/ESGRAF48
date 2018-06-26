#include "LateSkillsWidget.h"
#include "ui_LateSkillsWidget.h"

#include "PassivModel.h"
#include "GenitivModel.h"

LateSkillsWidget::LateSkillsWidget(QWidget *parent)
	: QWidget(parent)
    , ui(new Ui::LateSkillsWidget)
{
	ui->setupUi(this);
    ui->passivTableView->horizontalHeader()->hide();
    ui->genitivTableView->horizontalHeader()->hide();
}

LateSkillsWidget::~LateSkillsWidget()
{
	delete ui;
}

void LateSkillsWidget::setPassivModel(PassivModel *model)
{
    ui->passivTableView->setModel(model);
}
	
void LateSkillsWidget::setGenitivModel(GenitivModel *model)
{
    ui->genitivTableView->setModel(model);
}
