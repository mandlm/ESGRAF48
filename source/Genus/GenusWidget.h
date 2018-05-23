#pragma once

#include <QWidget>

class GenusModel;

namespace Ui {
class GenusWidget;
};

class GenusWidget : public QWidget
{
	Q_OBJECT

private:
	Ui::GenusWidget *ui;

public:
	GenusWidget(QWidget *parent = nullptr);
	~GenusWidget();

    void setModel(GenusModel *model);
};
