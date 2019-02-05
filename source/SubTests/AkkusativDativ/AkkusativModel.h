#pragma once

#include "PrintableModel.h"
#include "AkkusativModel.pb.h"

class AkkusativModel : public PrintableModel
{
	Q_OBJECT

public:
	AkkusativModel(QObject *parent);

	void read(const ESGRAF48::AkkusativModel &model);
	void write(ESGRAF48::AkkusativModel &model) const;

protected:
	void printHeader(QPainter &painter) const override;
};
