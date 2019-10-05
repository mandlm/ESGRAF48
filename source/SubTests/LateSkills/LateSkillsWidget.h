#pragma once

#include <QWidget>

class PassivModel;
class GenitivModel;

namespace Ui {
class LateSkillsWidget;
};

class LateSkillsWidget : public QWidget
{
    Q_OBJECT

private:
    Ui::LateSkillsWidget* ui;

public:
    LateSkillsWidget(QWidget* parent = nullptr);
    ~LateSkillsWidget();

    void setPassivModel(PassivModel* model);
    void setGenitivModel(GenitivModel* model);
};
