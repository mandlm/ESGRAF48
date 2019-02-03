#pragma once

#include "PrintableModel.h"
#include "V2SvkModel.pb.h"

class V2SvkModel : public PrintableModel
{
	Q_OBJECT

public:
	V2SvkModel(QObject *parent);

	virtual unsigned int getV2Points() const = 0;
	virtual unsigned int getSvkPoints() const = 0;

	virtual void write(ESGRAF48::V2SvkModel &model) const = 0;
	virtual void read(const ESGRAF48::V2SvkModel &model) = 0;

	static void printSummary(QPainter &painter, unsigned int v2Points, unsigned int svkPoints);

protected:
	void printTests(QPainter &painter) const override;
	void printSummary(QPainter &painter) const override {};

	virtual std::set<int> v2Tests() const = 0;
	virtual std::set<int> svkTests() const = 0;
};
