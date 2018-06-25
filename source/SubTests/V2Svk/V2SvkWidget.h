#pragma once

#include <QWidget>

class V2SvkModel;

namespace Ui {
class V2SvkWidget;
};

class V2SvkWidget : public QWidget
{
	Q_OBJECT

private:
	Ui::V2SvkWidget *ui;

public:
	V2SvkWidget(QWidget *parent = nullptr);
	~V2SvkWidget();

	void setV2SvkModel(V2SvkModel *model);
};
