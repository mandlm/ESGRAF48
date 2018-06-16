#include "DativModel.h"

DativModel::DativModel(QObject *parent)
	: CheckableTestModel(parent)
{
	m_tests = {
		{ "Dativ Nominalphrase", { "Tiger", "Katze", "Affe", "Gans", "Bär",
										 "Pferd", "Hund", "Elefant" } },
		{ "Präpositionalphrase (Verstecke)",
			{ "Vorhang", "Kiste", "Holz", "Kiste", "Baum", "Vorhang", "Holz",
				"Baum" } },
		{ "Nominalphrase (Tiere)", { "Salat", "Fleisch", "Knochen", "Banane",
										"Apfel", "Möhre", "Honig", "Zucker" } }
	};
}
