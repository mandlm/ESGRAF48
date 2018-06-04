#include "PluralModel.h"

PluralModel::PluralModel(QObject *parent)
	: CheckableTestModel(parent)
{
	m_tests = { { "",
		{ "Fisch /-e/", "Banane /-n/", "Bonbon /-s/", "Ei /-er/", "Eimer /-o/",
			"Korn UML+/-er/", "Nuss UML+/-e/", "Bär /-en/", "Apfel UML" } } };
}
