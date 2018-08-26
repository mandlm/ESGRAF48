#include "AkkusativModel.h"

AkkusativModel::AkkusativModel(QObject *parent)
	: CheckableTestModel(parent)
{
	m_tests = {
		{ "Akkusativ Nominalphrase", { "Tiger", "Katze", "Affe", "Gans", "Bär",
										 "Pferd", "Hund", "Elefant" } },
		{ "Präpositionalphrase (Verstecke)",
			{ "Vorhang", "Kiste", "Holz", "Kiste", "Baum", "Vorhang", "Holz",
				"Baum" } },
		{ "Nominalphrase (Futter)", { "Salat", "Fleisch", "Knochen", "Banane",
										"Apfel", "Karotte", "Honig", "Zucker" } }
	};
}
