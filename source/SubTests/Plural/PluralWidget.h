#pragma once

#include <QWidget>

class PluralModel;

namespace Ui {
class PluralWidget;
};

class PluralWidget : public QWidget
{
    Q_OBJECT

private:
    Ui::PluralWidget* ui;

public:
    PluralWidget(QWidget* parent = nullptr);
    ~PluralWidget();

    void setModel(PluralModel* model);
};
