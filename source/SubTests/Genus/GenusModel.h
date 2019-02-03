#pragma once

#include "PrintableModel.h"
#include "GenusModel.pb.h"

class GenusModel : public PrintableModel
{
	Q_OBJECT

public:
	GenusModel(QObject *parent);

	void read(const ESGRAF48::GenusModel &model);
	void write(ESGRAF48::GenusModel &model) const;
};
