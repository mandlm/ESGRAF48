#pragma once

#include "PrintableModel.h"

#include "CheckableTestModel.h"
#include "V2SvkModel.pb.h"

class WFModel : public CheckableTestModel, public PrintableModel
{
	Q_OBJECT

public:
	WFModel(QObject *parent);

	unsigned int getV2Points() const;
	unsigned int getSvkPoints() const;

	void write(ESGRAF48::V2SvkModel &model) const;
	void read(const ESGRAF48::V2SvkModel &model);

	void printTo(QPainter &painter) const override;

protected:
	bool isValidIndex(const QModelIndex &index) const override;
};
