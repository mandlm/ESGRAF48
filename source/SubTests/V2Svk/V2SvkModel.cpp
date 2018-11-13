#include "V2SvkModel.h"

V2SvkModel::V2SvkModel(QObject *parent)
	: CheckableTestModel(parent)
{
	m_tests = { 
		{ "W-Frage", 
			{ "Affe", "Affe", "Affe", "Affe", "Schwein", "Schwein", "Schwein", "Schwein", 
				"Gans" , "Gans", "Gans", "Gans"} },
		{ "Verbtrennung", 
			{ "", "Affe", "", "", "", "", "", "Schwein", "" , "", "Gans", ""} },
		{ "SVK: /-st/", 
			{ "Affe", "Affe", "Affe", "Affe", "Schwein", "Schwein", "Schwein", "Schwein", 
				"Gans" , "Gans", "Gans", "Gans"} },

		{ "Objekt-Topikalisierung", 
			{ "Affe", "Affe", "Affe", "Affe", "Schwein", "Schwein", "Schwein", "Schwein", 
				"Gans" , "Gans", "Gans", "Gans"} },
		{ "SVK: Stamm", 
			{ "Affe", "Affe", "Affe", "Affe", "Schwein", "Schwein", "Schwein", "Schwein", 
				"Gans" , "Gans", "Gans", "Gans"} },

		{ "Temporaladverb Präsens", 
			{ "Affe", "Affe", "Schwein", "Schwein", "Gans", "Gans" } },
		{ "SKV: /-e/ o. Stamm", 
			{ "Affe", "Affe", "Schwein", "Schwein", "Gans", "Gans" } },

		{ "Temporaladverb Perfekt", 
			{ "Affe", "Affe", "Schwein", "Schwein", "Gans", "Gans" } },
		{ "Verbtrennung", 
			{ "Affe", "Affe", "Schwein", "Schwein", "Gans", "Gans" } },
		{ "SVK: /-e/ o. Stamm", 
			{ "Affe", "Affe", "Schwein", "Schwein", "Gans", "Gans" } },
		{ "Partizip", 
			{ "Affe", "Affe", "Schwein", "Schwein", "Gans", "Gans" } },
	};
}

unsigned int V2SvkModel::getV2Points()
{
    unsigned int points = 0;

	for (auto testIndex : { 0, 1, 3, 5, 7, 8 })
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

unsigned int V2SvkModel::getSvkPoints()
{
    unsigned int points = 0;

	for (auto testIndex : { 2, 4, 6, 9, 10 })
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

void V2SvkModel::writeProtoBuf(ESGRAF48::V2SvkModel &model) const
{
	auto *wfrage = model.mutable_wfrage();
	if (wfrage != nullptr)
	{
		const auto &items = m_tests.at(0).items();

		wfrage->set_affe1(items[0].isChecked());
		wfrage->set_affe2(items[1].isChecked());
		wfrage->set_affe3(items[2].isChecked());
		wfrage->set_affe4(items[3].isChecked());
		wfrage->set_schwein1(items[4].isChecked());
		wfrage->set_schwein2(items[5].isChecked());
		wfrage->set_schwein3(items[6].isChecked());
		wfrage->set_schwein4(items[7].isChecked());
		wfrage->set_gans1(items[8].isChecked());
		wfrage->set_gans2(items[9].isChecked());
		wfrage->set_gans3(items[10].isChecked());
		wfrage->set_gans4(items[11].isChecked());
	}

	auto *verbtrennung = model.mutable_verbtrennung1();
	if (verbtrennung != nullptr)
	{
		const auto &testItems = m_tests.at(1).items();

		verbtrennung->set_affe(testItems[1].isChecked());
		verbtrennung->set_schwein(testItems[7].isChecked());
		verbtrennung->set_gans(testItems[10].isChecked());
	}
}
	
void V2SvkModel::readProtoBuf(const ESGRAF48::V2SvkModel &model)
{
	const auto &wfrage = model.wfrage();
	{
		auto &testItems = m_tests.at(0).items();

		testItems[0].setState(wfrage.affe1());
		testItems[1].setState(wfrage.affe2());
		testItems[2].setState(wfrage.affe3());
		testItems[3].setState(wfrage.affe4());
		testItems[4].setState(wfrage.schwein1());
		testItems[5].setState(wfrage.schwein2());
		testItems[6].setState(wfrage.schwein3());
		testItems[7].setState(wfrage.schwein4());
		testItems[8].setState(wfrage.gans1());
		testItems[9].setState(wfrage.gans2());
		testItems[10].setState(wfrage.gans3());
		testItems[11].setState(wfrage.gans4());
	}

	const auto &verbtrennung = model.verbtrennung1();
	{
		auto &testItems = m_tests.at(1).items();

		testItems[1].setState(verbtrennung.affe());
		testItems[7].setState(verbtrennung.schwein());
		testItems[10].setState(verbtrennung.gans());
	}

	emit dataChanged(index(0, 0), index(rowCount() - 1, columnCount() - 1));
}
