#pragma once

#include "CheckableTestModel.h"
#include "V2SvkModel.pb.h"

class V2SvkModel : public CheckableTestModel
{
	Q_OBJECT

public:
	V2SvkModel(QObject *parent);

	unsigned int getV2Points();
	unsigned int getSvkPoints();

	void writeProtoBuf(ESGRAF48::V2SvkModel &model) const;
	void readProtoBuf(const ESGRAF48::V2SvkModel &model);

protected:
	bool isValidIndex(const QModelIndex &index) const override;
};
