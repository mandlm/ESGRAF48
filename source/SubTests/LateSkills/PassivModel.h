#pragma once

#include "CheckableTestModel.h"

class PassivModel : public CheckableTestModel
{
	Q_OBJECT

public:
	PassivModel(QObject *parent);
	bool setData(const QModelIndex &index, const QVariant &value,
		int role = Qt::EditRole) override;
};
