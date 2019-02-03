#pragma once

#include "CheckableTestModel.h"
#include "PluralModel.pb.h"

class PluralModel : public CheckableTestModel
{
	Q_OBJECT

public:
	PluralModel(QObject *parent);

	void read(const ESGRAF48::PluralModel &model);
	void write(ESGRAF48::PluralModel &model) const;
};
