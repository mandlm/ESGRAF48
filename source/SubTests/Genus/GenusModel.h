#pragma once

#include "CheckableTestModel.h"
#include "GenusModel.pb.h"

class GenusModel : public CheckableTestModel
{
	Q_OBJECT

public:
	GenusModel(QObject *parent);

	void read(const ESGRAF48::GenusModel &model);
	void write(ESGRAF48::GenusModel &model) const;

protected:
	std::string getName() const override;
};
