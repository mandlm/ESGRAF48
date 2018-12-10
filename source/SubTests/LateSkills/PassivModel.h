#pragma once

#include "LateSkillsModel.h"
#include "LateSkillsPassivModel.pb.h"

class PassivModel : public LateSkillsModel
{
	Q_OBJECT

public:
	PassivModel(QObject *parent);
	bool setData(const QModelIndex &index, const QVariant &value,
		int role = Qt::EditRole) override;

	void read(const ESGRAF48::LateSkillsPassivModel &model);
	void write(ESGRAF48::LateSkillsPassivModel &model) const;

protected:
	std::string getName() const override;
};
