#pragma once

#include <QWidget>

class ResultModel;

namespace Ui {
class ResultWidget;
};

class ResultWidget : public QWidget
{
	Q_OBJECT

private:
        Ui::ResultWidget *ui;

public:
        ResultWidget(QWidget *parent = nullptr);
        ~ResultWidget();

		void setModel(ResultModel *model);
};
