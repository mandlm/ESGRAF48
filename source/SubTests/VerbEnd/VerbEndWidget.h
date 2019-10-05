#pragma once

#include <QWidget>

class VerbEndModel;

namespace Ui {
class VerbEndWidget;
};

class VerbEndWidget : public QWidget
{
    Q_OBJECT

private:
    Ui::VerbEndWidget* ui;

public:
    VerbEndWidget(QWidget* parent = nullptr);
    ~VerbEndWidget();

    void setModel(VerbEndModel* model);
};
