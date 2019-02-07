#include "PassivModel.h"

PassivModel::PassivModel(QObject *parent)
    : LateSkillsModel(parent)
{
	m_tests = {{"Passiv",
	            {"Elefant (1)", "Elefant (2)", "Pferde (1)", "Pferde (2)", "Bälle (1)", "Bälle (2)",
	             "Ball (1)", "Ball (2)", "Fleisch (1)", "Fleisch (2)"}}};

	for (auto index : {1, 3, 5, 7, 9})
	{
		m_tests[0].items()[index].setValue(2);
	}
}

bool PassivModel::setData(const QModelIndex &modelIndex, const QVariant &value, int role)
{
	if (role == Qt::CheckStateRole && value.toBool() == true)
	{
		if (modelIndex.column() % 2 == 0)
		{
			CheckableTestModel::setData(index(modelIndex.row(), modelIndex.column() + 1), false,
			                            role);
		}
		else
		{
			CheckableTestModel::setData(index(modelIndex.row(), modelIndex.column() - 1), false,
			                            role);
		}
	}

	return CheckableTestModel::setData(modelIndex, value, role);
}

void PassivModel::read(const ESGRAF48::LateSkillsPassivModel &model)
{
	auto &testItems = m_tests.at(0).items();

	testItems[0].setState(model.elefant1());
	testItems[1].setState(model.elefant2());
	testItems[2].setState(model.pferde1());
	testItems[3].setState(model.pferde2());
	testItems[4].setState(model.baelle1());
	testItems[5].setState(model.baelle2());
	testItems[6].setState(model.ball1());
	testItems[7].setState(model.ball2());
	testItems[8].setState(model.fleisch1());
	testItems[9].setState(model.fleisch2());

	emit dataChanged(index(0, 0), index(rowCount() - 1, columnCount() - 1));
}

void PassivModel::write(ESGRAF48::LateSkillsPassivModel &model) const
{
	const auto &testItems = m_tests.at(0).items();

	model.set_elefant1(testItems[0].isChecked());
	model.set_elefant2(testItems[1].isChecked());
	model.set_pferde1(testItems[2].isChecked());
	model.set_pferde2(testItems[3].isChecked());
	model.set_baelle1(testItems[4].isChecked());
	model.set_baelle2(testItems[5].isChecked());
	model.set_ball1(testItems[6].isChecked());
	model.set_ball2(testItems[7].isChecked());
	model.set_fleisch1(testItems[8].isChecked());
	model.set_fleisch2(testItems[9].isChecked());
}
	
void PassivModel::printHeader(QPainter &painter) const
{
	drawHeader2(painter, "Subtest 6: Späte Fähigkeiten (7;0-8;11)");
}
