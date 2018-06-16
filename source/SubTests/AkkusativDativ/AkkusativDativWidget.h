#pragma once

#include <QWidget>

class AkkusativModel;
class DativModel;

namespace Ui {
class AkkusativDativWidget;
};

class AkkusativDativWidget : public QWidget
{
	Q_OBJECT

private:
	Ui::AkkusativDativWidget *ui;

public:
	AkkusativDativWidget(QWidget *parent = nullptr);
	~AkkusativDativWidget();

	void setAkkusativModel(AkkusativModel *model);
	void setDativModel(DativModel *model);
};
