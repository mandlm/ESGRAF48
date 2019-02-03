#pragma once

#include "PrintableModel.h"
#include "VerbEndModel.pb.h"

class VerbEndModel : public PrintableModel
{
	Q_OBJECT

public:
	VerbEndModel(QObject *parent);

	void write(ESGRAF48::VerbEndModel &model) const;
	void read(const ESGRAF48::VerbEndModel &model);
};
