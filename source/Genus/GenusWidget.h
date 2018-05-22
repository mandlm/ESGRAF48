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
	GenusModel *m_model;

public:
	GenusWidget(QWidget *parent = nullptr);
	~GenusWidget();
};
