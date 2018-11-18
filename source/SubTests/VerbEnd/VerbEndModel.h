#pragma once

#include "CheckableTestModel.h"
#include "VerbEndModel.pb.h"

class VerbEndModel : public CheckableTestModel
{
	Q_OBJECT

public:
	VerbEndModel(QObject *parent);

	void writeProtoBuf(ESGRAF48::VerbEndModel &model) const;
	void readProtoBuf(const ESGRAF48::VerbEndModel &model);
};
