#pragma once

#include "CheckableTestModel.h"
#include "LateSkillsGenitivModel.pb.h"

class GenitivModel : public CheckableTestModel
{
	Q_OBJECT

public:
	GenitivModel(QObject *parent);
	bool setData(const QModelIndex &index, const QVariant &value,
		int role = Qt::EditRole) override;

	void read(const ESGRAF48::LateSkillsGenitivModel &model);
	void write(ESGRAF48::LateSkillsGenitivModel &model) const;
};
