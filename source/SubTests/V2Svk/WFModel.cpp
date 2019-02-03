#include "WFModel.h"

WFModel::WFModel(QObject *parent)
    : V2SvkModel(parent)
{
	m_title = "Subtest 1: Verbzweitstellungsregel (V2) und Subjekt-Verb-Kontrollregel (SVK)";

	m_tests = {
	    {"W-Frage",
	     {"Affe", "Affe", "Affe", "Affe", "Schwein", "Schwein", "Schwein", "Schwein", "Gans",
	      "Gans", "Gans", "Gans"}},
	    {"Verbtrennung", {"", "Affe", "", "", "", "", "", "Schwein", "", "", "Gans", ""}},
	    {"SVK: /-st/",
	     {"Affe", "Affe", "Affe", "Affe", "Schwein", "Schwein", "Schwein", "Schwein", "Gans",
	      "Gans", "Gans", "Gans"}},
	};
}

unsigned int WFModel::getV2Points() const
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

unsigned int WFModel::getSvkPoints() const
{
	unsigned int points = 0;

	for (auto testIndex : {2})
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

bool WFModel::isValidIndex(const QModelIndex &index) const
{
	if (index.row() == 1)
	{
		return index.column() == 1 || index.column() == 7 || index.column() == 10;
	}

	return CheckableTestModel::isValidIndex(index);
}

void WFModel::write(ESGRAF48::V2SvkModel &model) const
{
	auto writeOneVal = [&](ESGRAF48::V2SvkModel::OneEach *modelData, int testIndex) {
		if (modelData != nullptr)
		{
			const auto &testItems = m_tests.at(testIndex).items();

			modelData->set_affe(testItems[1].isChecked());
			modelData->set_schwein(testItems[7].isChecked());
			modelData->set_gans(testItems[10].isChecked());
		}
	};

	auto writeFourVals = [&](ESGRAF48::V2SvkModel::FourEach *modelData, int testIndex) {
		if (modelData != nullptr)
		{
			const auto &testItems = m_tests.at(testIndex).items();

			modelData->set_affe1(testItems[0].isChecked());
			modelData->set_affe2(testItems[1].isChecked());
			modelData->set_affe3(testItems[2].isChecked());
			modelData->set_affe4(testItems[3].isChecked());
			modelData->set_schwein1(testItems[4].isChecked());
			modelData->set_schwein2(testItems[5].isChecked());
			modelData->set_schwein3(testItems[6].isChecked());
			modelData->set_schwein4(testItems[7].isChecked());
			modelData->set_gans1(testItems[8].isChecked());
			modelData->set_gans2(testItems[9].isChecked());
			modelData->set_gans3(testItems[10].isChecked());
			modelData->set_gans4(testItems[11].isChecked());
		}
	};

	writeFourVals(model.mutable_wfrage(), 0);
	writeOneVal(model.mutable_verbtrennung1(), 1);
}

void WFModel::read(const ESGRAF48::V2SvkModel &model)
{
	auto readOneVal = [&](const ESGRAF48::V2SvkModel::OneEach &modelData, int testIndex) {
		auto &testItems = m_tests.at(testIndex).items();

		testItems[1].setState(modelData.affe());
		testItems[7].setState(modelData.schwein());
		testItems[10].setState(modelData.gans());
	};

	auto readFourVals = [&](const ESGRAF48::V2SvkModel::FourEach &modelData, int testIndex) {
		auto &testItems = m_tests.at(testIndex).items();

		testItems[0].setState(modelData.affe1());
		testItems[1].setState(modelData.affe2());
		testItems[2].setState(modelData.affe3());
		testItems[3].setState(modelData.affe4());
		testItems[4].setState(modelData.schwein1());
		testItems[5].setState(modelData.schwein2());
		testItems[6].setState(modelData.schwein3());
		testItems[7].setState(modelData.schwein4());
		testItems[8].setState(modelData.gans1());
		testItems[9].setState(modelData.gans2());
		testItems[10].setState(modelData.gans3());
		testItems[11].setState(modelData.gans4());
	};

	readFourVals(model.wfrage(), 0);
	readOneVal(model.verbtrennung1(), 1);

	emit dataChanged(index(0, 0), index(rowCount() - 1, columnCount() - 1));
}

std::set<int> WFModel::v2Tests() const
{
	return {0, 1};
};

std::set<int> WFModel::svkTests() const
{
	return {2};
};
