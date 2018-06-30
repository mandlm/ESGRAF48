#include "GenitivModel.h"

GenitivModel::GenitivModel(QObject *parent)
	: CheckableTestModel(parent)
{
	m_tests = {
		{ "Genitiv Präpositionen",
			{ "anstelle (1)", "anstelle (2)", "außerhalb (1)", "außerhalb (2)",
				"mithilfe (1)", "mithilfe (2)" } },
		{ "Attributierung",
			{ "Schuhe (1)", "Schuhe (2)", "Zauberstab (1)", "Zauberstab (2)",
				"Hut (1)", "Hut (2)", "Brille (1)", "Brille (2)", "Gürtel (1)",
				"Gürtel (2)" } },
	};

	for (auto index : { 1, 3, 5 })
	{
		m_tests[0].items()[index].setValue(2);
	}

	for (auto index : { 1, 3, 5, 7, 9 })
	{
		m_tests[1].items()[index].setValue(2);
	}
}

bool GenitivModel::setData(
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
