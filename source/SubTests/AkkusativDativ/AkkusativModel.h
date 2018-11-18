#pragma once

#include "CheckableTestModel.h"
#include "AkkusativModel.pb.h"

class AkkusativModel : public CheckableTestModel
{
	Q_OBJECT

public:
	AkkusativModel(QObject *parent);

	void read(const ESGRAF48::AkkusativModel &model);
	void write(ESGRAF48::AkkusativModel &model) const;
};
