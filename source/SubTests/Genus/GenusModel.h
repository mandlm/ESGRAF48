#pragma once

#include "CheckableTestModel.h"
#include "GenusModel.pb.h"

class GenusModel : public CheckableTestModel
{
	Q_OBJECT

public:
	GenusModel(QObject *parent);

	void readProtoBuf(const ESGRAF48::GenusModel &model);
	void writeProtoBuf(ESGRAF48::GenusModel &model) const;
};
