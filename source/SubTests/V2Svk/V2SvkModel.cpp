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
