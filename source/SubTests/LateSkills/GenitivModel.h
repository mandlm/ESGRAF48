#pragma once

#include "CheckableTestModel.h"

class GenitivModel : public CheckableTestModel
{
	Q_OBJECT

public:
	GenitivModel(QObject *parent);
	bool setData(const QModelIndex &index, const QVariant &value,
		int role = Qt::EditRole) override;
};
