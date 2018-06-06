#pragma once

#include <QWidget>

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
};
