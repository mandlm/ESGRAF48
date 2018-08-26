#pragma once

#include "CheckableTestModel.h"

class PluralModel : public CheckableTestModel
{
	Q_OBJECT

public:
	PluralModel(QObject *parent);

    QVariant data(
        const QModelIndex &index, int role = Qt::DisplayRole) const override;
};
