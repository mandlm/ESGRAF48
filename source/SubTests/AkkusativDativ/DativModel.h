#pragma once

#include "PrintableModel.h"
#include "DativModel.pb.h"

class DativModel : public PrintableModel
{
	Q_OBJECT

public:
	DativModel(QObject *parent);

	void read(const ESGRAF48::DativModel &model);
	void write(ESGRAF48::DativModel &model) const;

protected:
	void printHeader(QPainter &) const override {};
};
