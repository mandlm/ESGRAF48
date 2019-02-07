#pragma once

#include "PrintableModel.h"
#include "LateSkillsPassivModel.pb.h"

class LateSkillsModel : public PrintableModel
{
	Q_OBJECT

public:
	LateSkillsModel(QObject *parent);

protected:
	void printTests(QPainter &painter) const override;
};
