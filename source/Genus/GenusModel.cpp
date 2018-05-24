#include "GenusModel.h"

GenusModel::GenusModel(QObject *parent)
	: CheckableTestModel(parent)
{
	m_tests = { { "Tiere", { "Tiger", "Bär", "Katze", "Pferd", "Gans",
							   "Elefant", "Katze", "Hund" } },
		{ "Futter", { "Salat", "Fleisch", "Knocken", "Banane", "Apfel", "Möhre",
						"Honig", "Zucker" } },
		{ "Zirkus", { "Kiste", "Holz", "Vorhang", "Baum" } } };
}
