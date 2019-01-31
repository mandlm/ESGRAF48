#pragma once

#include "CheckableTestModel.h"
#include "V2SvkModel.pb.h"

class OTModel : public CheckableTestModel
{
	Q_OBJECT

public:
	OTModel(QObject *parent);

	unsigned int getV2Points();
	unsigned int getSvkPoints();

	void write(ESGRAF48::V2SvkModel &model) const;
	void read(const ESGRAF48::V2SvkModel &model);
};
