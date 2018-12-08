#include "AkkusativModel.h"

AkkusativModel::AkkusativModel(QObject *parent)
    : CheckableTestModel(parent)
{
	m_tests = {{"Akkusativ Nominalphrase",
	            {"Tiger", "Katze", "Affe", "Gans", "Bär", "Pferd", "Hund", "Elefant"}},
	           {"Präpositionalphrase (Verstecke)",
	            {"Vorhang", "Kiste", "Holz", "Kiste", "Baum", "Vorhang", "Holz", "Baum"}},
	           {"Nominalphrase (Futter)",
	            {"Salat", "Fleisch", "Knochen", "Banane", "Apfel", "Karotte", "Honig", "Zucker"}}};
}

void AkkusativModel::read(const ESGRAF48::AkkusativModel &model)
{
	const auto &tiereModel = model.tiere();
	{
		auto &testItems = m_tests.at(0).items();

		testItems[0].setState(tiereModel.tiger());
		testItems[1].setState(tiereModel.katze());
		testItems[2].setState(tiereModel.affe());
		testItems[3].setState(tiereModel.gans());
		testItems[4].setState(tiereModel.baer());
		testItems[5].setState(tiereModel.pferd());
		testItems[6].setState(tiereModel.hund());
		testItems[7].setState(tiereModel.elefant());
	}

	const auto &versteckeModel = model.verstecke();
	{
		auto &testItems = m_tests.at(1).items();

		testItems[0].setState(versteckeModel.vorhang1());
		testItems[1].setState(versteckeModel.kiste1());
		testItems[2].setState(versteckeModel.holz1());
		testItems[3].setState(versteckeModel.kiste2());
		testItems[4].setState(versteckeModel.baum1());
		testItems[5].setState(versteckeModel.vorhang2());
		testItems[6].setState(versteckeModel.holz2());
		testItems[7].setState(versteckeModel.baum2());
	}

	const auto &futterModel = model.futter();
	{
		auto &testItems = m_tests.at(2).items();

		testItems[0].setState(futterModel.salat());
		testItems[1].setState(futterModel.fleisch());
		testItems[2].setState(futterModel.knochen());
		testItems[3].setState(futterModel.banane());
		testItems[4].setState(futterModel.apfel());
		testItems[5].setState(futterModel.karotte());
		testItems[6].setState(futterModel.honig());
		testItems[7].setState(futterModel.zucker());
	}

	emit dataChanged(index(0, 0), index(rowCount() - 1, columnCount() - 1));
}

void AkkusativModel::write(ESGRAF48::AkkusativModel &model) const
{
	auto *tiereModel = model.mutable_tiere();
	if (tiereModel != nullptr)
	{
		const auto &testItems = m_tests.at(0).items();

		tiereModel->set_tiger(testItems[0].isChecked());
		tiereModel->set_katze(testItems[1].isChecked());
		tiereModel->set_affe(testItems[2].isChecked());
		tiereModel->set_gans(testItems[3].isChecked());
		tiereModel->set_baer(testItems[4].isChecked());
		tiereModel->set_pferd(testItems[5].isChecked());
		tiereModel->set_hund(testItems[6].isChecked());
		tiereModel->set_elefant(testItems[7].isChecked());
	}

	auto *versteckeModel = model.mutable_verstecke();
	if (versteckeModel != nullptr)
	{
		const auto &testItems = m_tests.at(1).items();

		versteckeModel->set_vorhang1(testItems[0].isChecked());
		versteckeModel->set_kiste1(testItems[1].isChecked());
		versteckeModel->set_holz1(testItems[2].isChecked());
		versteckeModel->set_kiste2(testItems[3].isChecked());
		versteckeModel->set_baum1(testItems[4].isChecked());
		versteckeModel->set_vorhang2(testItems[5].isChecked());
		versteckeModel->set_holz2(testItems[6].isChecked());
		versteckeModel->set_baum2(testItems[7].isChecked());
	}

	auto *futterModel = model.mutable_futter();
	if (futterModel != nullptr)
	{
		const auto &testItems = m_tests.at(2).items();

		futterModel->set_salat(testItems[0].isChecked());
		futterModel->set_fleisch(testItems[1].isChecked());
		futterModel->set_knochen(testItems[2].isChecked());
		futterModel->set_banane(testItems[3].isChecked());
		futterModel->set_apfel(testItems[4].isChecked());
		futterModel->set_karotte(testItems[5].isChecked());
		futterModel->set_honig(testItems[6].isChecked());
		futterModel->set_zucker(testItems[7].isChecked());
	}
}
	
std::string AkkusativModel::getName() const
{
	return "Subtest 4: Akkusativ und Dativ";
}
