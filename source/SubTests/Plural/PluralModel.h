#pragma once

#include "CheckableTestModel.h"
#include "PluralModel.pb.h"

class PluralModel : public CheckableTestModel
{
	Q_OBJECT

public:
	PluralModel(QObject *parent);

    QVariant data(
        const QModelIndex &index, int role = Qt::DisplayRole) const override;

	void read(const ESGRAF48::PluralModel &model);
	void write(ESGRAF48::PluralModel &model) const;

protected:
	std::string getName() const override;
};
