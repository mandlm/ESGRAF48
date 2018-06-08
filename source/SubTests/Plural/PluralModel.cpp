#include "PluralModel.h"

PluralModel::PluralModel(QObject *parent)
	: CheckableTestModel(parent)
{
	m_tests = { { "",
		{ "Fisch /-e/", "Banane /-n/", "Bonbon /-s/", "Ei /-er/", "Eimer /-ø/",
			"Korn UML+/-er/", "Nuss UML+/-e/", "Bär /-en/", "Apfel UML" } } };
}

size_t PluralModel::getPoints() const
{
	size_t points = 0;

	for (const auto &test : m_tests)
	{
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
