#pragma once

#include <QWidget>

class QDataWidgetMapper;
class MetaDataModel;

namespace Ui {
class MetaDataWidget;
};

class MetaDataWidget : public QWidget
{
    Q_OBJECT

private:
    Ui::MetaDataWidget* ui;
    QDataWidgetMapper* m_widgetMapper;

public:
    MetaDataWidget(QWidget* parent = nullptr);
    ~MetaDataWidget();

    void setModel(MetaDataModel* model);
    void toFirst();
};
