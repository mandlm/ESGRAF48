#pragma once

#include "CheckableTestModel.h"

class LateSkillsModel : public CheckableTestModel
{
	Q_OBJECT

public:
	LateSkillsModel(QObject *parent);

protected:
	void printTableTo(QTextCursor &cursor) const override;
};
