#pragma once

#include "CheckableTestModel.h"
#include "DativModel.pb.h"

class DativModel : public CheckableTestModel
{
	Q_OBJECT

public:
	DativModel(QObject *parent);

	void read(const ESGRAF48::DativModel &model);
	void write(ESGRAF48::DativModel &model) const;
};
