#pragma once

#include "CheckableTestModel.h"

class V2SvkModel : public CheckableTestModel
{
	Q_OBJECT

public:
	V2SvkModel(QObject *parent);

	unsigned int getV2Points();
	unsigned int getSvkPoints();
};
