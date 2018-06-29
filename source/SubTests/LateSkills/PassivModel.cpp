#include "PassivModel.h"

PassivModel::PassivModel(QObject *parent)
	: CheckableTestModel(parent)
{
	m_tests = { { "Passiv",
		{ "Elefant (1)", "Elefant (2)", "Pferde (1)", "Pferde (2)", "Bälle (1)",
			"Bälle (2)", "Ball (1)", "Ball (2)", "Fleisch (1)",
			"Fleisch (2)" } } };

	for (auto index : { 1, 3, 5, 7, 9 })
	{
		m_tests[0].items()[index].setValue(2);
	}
}

bool PassivModel::setData(
	const QModelIndex &modelIndex, const QVariant &value, int role)
{
	if (role == Qt::CheckStateRole && value.toBool() == true)
	{
		if (modelIndex.column() % 2 == 0)
		{
			CheckableTestModel::setData(
				index(modelIndex.row(), modelIndex.column() + 1), false, role);
		}
		else
		{
			CheckableTestModel::setData(
				index(modelIndex.row(), modelIndex.column() - 1), false, role);
		}
	}

	return CheckableTestModel::setData(modelIndex, value, role);
}
