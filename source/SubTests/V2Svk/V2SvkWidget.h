#pragma once

#include <QWidget>

class WFModel;
class OTModel;
class TPrModel;
class TPeModel;

namespace Ui {
class V2SvkWidget;
};

class V2SvkWidget : public QWidget
{
    Q_OBJECT

private:
    Ui::V2SvkWidget* ui;

public:
    V2SvkWidget(QWidget* parent = nullptr);
    ~V2SvkWidget();

    void setWFModel(WFModel* model);
    void setOTModel(OTModel* model);
    void setTPrModel(TPrModel* model);
    void setTPeModel(TPeModel* model);
};
