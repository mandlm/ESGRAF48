#pragma once

#include <QWidget>

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
};
