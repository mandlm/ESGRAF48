#pragma once

#include "CheckableTestModel.h"

class PluralModel : public CheckableTestModel
{
	Q_OBJECT

public:
	PluralModel(QObject *parent);

	size_t getPoints() const;

signals:
	void resultChanged(size_t result) const;
};
