#include "MetaDataWidget.h"
#include "ui_MetaDataWidget.h"

#include "MetaDataModel.h"

#include <QDataWidgetMapper>

MetaDataWidget::MetaDataWidget(QWidget *parent)
	: QWidget(parent)
	, ui(new Ui::MetaDataWidget)
	, m_widgetMapper(new QDataWidgetMapper(this))
{
	ui->setupUi(this);
}

MetaDataWidget::~MetaDataWidget()
{
	delete ui;
}

void MetaDataWidget::setModel(MetaDataModel *model)
{
	m_widgetMapper->setModel(model);
	m_widgetMapper->addMapping(ui->participantLineEdit, 0);
	m_widgetMapper->addMapping(ui->instructorLineEdit, 1);
	m_widgetMapper->addMapping(ui->dateOfBirthDateEdit, 2);
	m_widgetMapper->addMapping(ui->dateOfTestDateEdit, 3);
	m_widgetMapper->addMapping(ui->remarksPlainTextEdit, 4);
	m_widgetMapper->toFirst();
}

void MetaDataWidget::toFirst()
{
	m_widgetMapper->toFirst();
}
