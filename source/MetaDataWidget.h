#pragma once

#include <QWidget>

namespace Ui {
class MetaDataWidget;
};

class MetaDataWidget : public QWidget
{
	Q_OBJECT

private:
	Ui::MetaDataWidget *ui;

public:
	MetaDataWidget(QWidget *parent = nullptr);
	~MetaDataWidget();
};
