#pragma once

#include "PrintableModel.h"
#include "PluralModel.pb.h"

class PluralModel : public PrintableModel
{
	Q_OBJECT

public:
	PluralModel(QObject *parent);

	void read(const ESGRAF48::PluralModel &model);
	void write(ESGRAF48::PluralModel &model) const;
};
