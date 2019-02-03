#include "TPeModel.h"

TPeModel::TPeModel(QObject *parent)
    : CheckableTestModel(parent)
{
	m_tests = {
	    {"Temporaladverb Perfekt", {"Affe", "Affe", "Schwein", "Schwein", "Gans", "Gans"}},
	    {"Verbtrennung", {"Affe", "Affe", "Schwein", "Schwein", "Gans", "Gans"}},
	    {"SVK: /-e/ o. Stamm", {"Affe", "Affe", "Schwein", "Schwein", "Gans", "Gans"}},
	    {"Partizip", {"Affe", "Affe", "Schwein", "Schwein", "Gans", "Gans"}},
	};
}

unsigned int TPeModel::getV2Points()
{
	unsigned int points = 0;

	for (auto testIndex : {0, 1})
	{
		const auto &test = m_tests.at(testIndex);

		for (const auto &item : test.items())
		{
			if (item.isChecked())
			{
				points++;
			}
		}
	}

	return points;
}

unsigned int TPeModel::getSvkPoints()
{
	unsigned int points = 0;

	for (auto testIndex : {2, 3})
	{
		const auto &test = m_tests.at(testIndex);

		for (const auto &item : test.items())
		{
			if (item.isChecked())
			{
				points++;
			}
		}
	}

	return points;
}

void TPeModel::write(ESGRAF48::V2SvkModel &model) const
{
	auto writeTwoVals = [&](ESGRAF48::V2SvkModel::TwoEach *modelData, int testIndex) {
		if (modelData != nullptr)
		{
			const auto &testItems = m_tests.at(testIndex).items();

			modelData->set_affe1(testItems[0].isChecked());
			modelData->set_affe2(testItems[1].isChecked());
			modelData->set_schwein1(testItems[2].isChecked());
			modelData->set_schwein2(testItems[3].isChecked());
			modelData->set_gans1(testItems[4].isChecked());
			modelData->set_gans2(testItems[5].isChecked());
		}
	};

	writeTwoVals(model.mutable_tempperf(), 0);
	writeTwoVals(model.mutable_verbtrennung2(), 1);
	writeTwoVals(model.mutable_svke2(), 2);
	writeTwoVals(model.mutable_partizip(), 3);
}

void TPeModel::read(const ESGRAF48::V2SvkModel &model)
{
	auto readTwoVals = [&](const ESGRAF48::V2SvkModel::TwoEach &modelData, int testIndex) {
		auto &testItems = m_tests.at(testIndex).items();

		testItems[0].setState(modelData.affe1());
		testItems[1].setState(modelData.affe2());
		testItems[2].setState(modelData.schwein1());
		testItems[3].setState(modelData.schwein2());
		testItems[4].setState(modelData.gans1());
		testItems[5].setState(modelData.gans2());
	};

	readTwoVals(model.tempperf(), 0);
	readTwoVals(model.verbtrennung2(), 1);
	readTwoVals(model.svke2(), 2);
	readTwoVals(model.partizip(), 3);

	emit dataChanged(index(0, 0), index(rowCount() - 1, columnCount() - 1));
}
