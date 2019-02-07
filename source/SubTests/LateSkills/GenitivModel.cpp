#include "GenitivModel.h"

GenitivModel::GenitivModel(QObject *parent)
    : LateSkillsModel(parent)
{
	m_tests = {
	    {"Genitiv Präpositionen",
	     {"anstelle (1)", "anstelle (2)", "außerhalb (1)", "außerhalb (2)", "mithilfe (1)",
	      "mithilfe (2)"}},
	    {"Attributierung",
	     {"Schuhe (1)", "Schuhe (2)", "Zauberstab (1)", "Zauberstab (2)", "Hut (1)", "Hut (2)",
	      "Brille (1)", "Brille (2)", "Gürtel (1)", "Gürtel (2)"}},
	};

	for (auto index : {1, 3, 5})
	{
		m_tests[0].items()[index].setValue(2);
	}

	for (auto index : {1, 3, 5, 7, 9})
	{
		m_tests[1].items()[index].setValue(2);
	}
}

bool GenitivModel::setData(const QModelIndex &modelIndex, const QVariant &value, int role)
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

void GenitivModel::read(const ESGRAF48::LateSkillsGenitivModel &model)
{
	const auto &praepositionenModel = model.praepositionen();
	{
		auto &testItems = m_tests.at(0).items();

		testItems[0].setState(praepositionenModel.anstelle1());
		testItems[1].setState(praepositionenModel.anstelle2());
		testItems[2].setState(praepositionenModel.ausserhalb1());
		testItems[3].setState(praepositionenModel.ausserhalb2());
		testItems[4].setState(praepositionenModel.mithilfe1());
		testItems[5].setState(praepositionenModel.mithilfe2());
	}

	const auto &attributierungModel = model.attributierung();
	{
		auto &testItems = m_tests.at(1).items();

		testItems[0].setState(attributierungModel.schuhe1());
		testItems[1].setState(attributierungModel.schuhe2());
		testItems[2].setState(attributierungModel.zauberstab1());
		testItems[3].setState(attributierungModel.zauberstab2());
		testItems[4].setState(attributierungModel.hut1());
		testItems[5].setState(attributierungModel.hut2());
		testItems[6].setState(attributierungModel.brille1());
		testItems[7].setState(attributierungModel.brille2());
		testItems[8].setState(attributierungModel.guertel1());
		testItems[9].setState(attributierungModel.guertel2());
	}

	emit dataChanged(index(0, 0), index(rowCount() - 1, columnCount() - 1));
}

void GenitivModel::write(ESGRAF48::LateSkillsGenitivModel &model) const
{
	auto *praepositionenModel = model.mutable_praepositionen();
	if (praepositionenModel != nullptr)
	{
		const auto &testItems = m_tests.at(0).items();

		praepositionenModel->set_anstelle1(testItems[0].isChecked());
		praepositionenModel->set_anstelle2(testItems[1].isChecked());
		praepositionenModel->set_ausserhalb1(testItems[2].isChecked());
		praepositionenModel->set_ausserhalb2(testItems[3].isChecked());
		praepositionenModel->set_mithilfe1(testItems[4].isChecked());
		praepositionenModel->set_mithilfe2(testItems[5].isChecked());
	}

	auto *attributierungModel = model.mutable_attributierung();
	if (attributierungModel != nullptr)
	{
		const auto &testItems = m_tests.at(1).items();

		attributierungModel->set_schuhe1(testItems[0].isChecked());
		attributierungModel->set_schuhe2(testItems[1].isChecked());
		attributierungModel->set_zauberstab1(testItems[2].isChecked());
		attributierungModel->set_zauberstab2(testItems[3].isChecked());
		attributierungModel->set_hut1(testItems[4].isChecked());
		attributierungModel->set_hut2(testItems[5].isChecked());
		attributierungModel->set_brille1(testItems[6].isChecked());
		attributierungModel->set_brille2(testItems[7].isChecked());
		attributierungModel->set_guertel1(testItems[8].isChecked());
		attributierungModel->set_guertel2(testItems[9].isChecked());
	}
}
	
void GenitivModel::printHeader(QPainter &painter) const
{
	painter.translate(0, -1.5 * painter.fontMetrics().lineSpacing());
}
