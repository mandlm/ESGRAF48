#include "DativModel.h"

DativModel::DativModel(QObject *parent)
    : CheckableTestModel(parent)
{
	m_tests = {{"Dativ Nominalphrase",
	            {"Affe", "Gans", "Tiger", "Hund", "Elefant", "Pferd", "Bär", "Katze"}},
	           {"Präpositionalphrase (Verstecke)",
	            {"Vorhang", "Kiste", "Holz", "Kiste", "Baum", "Vorhang", "Holz", "Baum"}},
	           {"Nominalphrase (Tiere)",
	            {"Gans", "Tiger", "Hund", "Affe", "Elefant", "Pferd", "Bär", "Katze"}}};
}

void DativModel::read(const ESGRAF48::DativModel &model)
{
	const auto &tiereModel = model.tiere();
	{
		auto &testItems = m_tests.at(0).items();

		testItems[0].setState(tiereModel.affe());
		testItems[1].setState(tiereModel.gans());
		testItems[2].setState(tiereModel.tiger());
		testItems[3].setState(tiereModel.hund());
		testItems[4].setState(tiereModel.elefant());
		testItems[5].setState(tiereModel.pferd());
		testItems[6].setState(tiereModel.baer());
		testItems[7].setState(tiereModel.katze());
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

	const auto &nomTiereModel = model.nomtiere();
	{
		auto &testItems = m_tests.at(2).items();

		testItems[0].setState(nomTiereModel.gans());
		testItems[1].setState(nomTiereModel.tiger());
		testItems[2].setState(nomTiereModel.hund());
		testItems[3].setState(nomTiereModel.affe());
		testItems[4].setState(nomTiereModel.elefant());
		testItems[5].setState(nomTiereModel.pferd());
		testItems[6].setState(nomTiereModel.baer());
		testItems[7].setState(nomTiereModel.katze());
	}

	emit dataChanged(index(0, 0), index(rowCount() - 1, columnCount() - 1));
}

void DativModel::write(ESGRAF48::DativModel &model) const
{
	auto *tiereModel = model.mutable_tiere();
	if (tiereModel != nullptr)
	{
		const auto &testItems = m_tests.at(0).items();

		tiereModel->set_affe(testItems[0].isChecked());
		tiereModel->set_gans(testItems[1].isChecked());
		tiereModel->set_tiger(testItems[2].isChecked());
		tiereModel->set_hund(testItems[3].isChecked());
		tiereModel->set_elefant(testItems[4].isChecked());
		tiereModel->set_pferd(testItems[5].isChecked());
		tiereModel->set_baer(testItems[6].isChecked());
		tiereModel->set_katze(testItems[7].isChecked());
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

	auto *nomTiereModel = model.mutable_nomtiere();
	if (nomTiereModel != nullptr)
	{
		const auto &testItems = m_tests.at(2).items();

		nomTiereModel->set_gans(testItems[0].isChecked());
		nomTiereModel->set_tiger(testItems[1].isChecked());
		nomTiereModel->set_hund(testItems[2].isChecked());
		nomTiereModel->set_affe(testItems[3].isChecked());
		nomTiereModel->set_elefant(testItems[4].isChecked());
		nomTiereModel->set_pferd(testItems[5].isChecked());
		nomTiereModel->set_baer(testItems[6].isChecked());
		nomTiereModel->set_katze(testItems[7].isChecked());
	}
}
