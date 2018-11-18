#include "GenusModel.h"

GenusModel::GenusModel(QObject *parent)
    : CheckableTestModel(parent)
{
	m_tests = {{"Tiere", {"Tiger", "Bär", "Katze", "Pferd", "Gans", "Elefant", "Affe", "Hund"}},
	           {"Futter",
	            {"Salat", "Fleisch", "Knochen", "Banane", "Apfel", "Karotte", "Honig", "Zucker"}},
	           {"Zirkus", {"Kiste", "Holz", "Vorhang", "Baum"}}};
}

void GenusModel::readProtoBuf(const ESGRAF48::GenusModel &model)
{
	const auto &tiereModel = model.tiere();
	{
		auto &testItems = m_tests.at(0).items();

		testItems[0].setState(tiereModel.tiger());
		testItems[1].setState(tiereModel.baer());
		testItems[2].setState(tiereModel.katze());
		testItems[3].setState(tiereModel.pferd());
		testItems[4].setState(tiereModel.gans());
		testItems[5].setState(tiereModel.elefant());
		testItems[6].setState(tiereModel.affe());
		testItems[7].setState(tiereModel.hund());
	}

	const auto &futterModel = model.futter();
	{
		auto &testItems = m_tests.at(1).items();

		testItems[0].setState(futterModel.salat());
		testItems[1].setState(futterModel.fleisch());
		testItems[2].setState(futterModel.knochen());
		testItems[3].setState(futterModel.banane());
		testItems[4].setState(futterModel.apfel());
		testItems[5].setState(futterModel.karotte());
		testItems[6].setState(futterModel.honig());
		testItems[7].setState(futterModel.zucker());
	}

	const auto &zirkusModel = model.zirkus();
	{
		auto &testItems = m_tests.at(2).items();

		testItems[0].setState(zirkusModel.kiste());
		testItems[1].setState(zirkusModel.holz());
		testItems[2].setState(zirkusModel.vorhang());
		testItems[3].setState(zirkusModel.baum());
	}

	emit dataChanged(index(0, 0), index(rowCount() - 1, columnCount() - 1));
}

void GenusModel::writeProtoBuf(ESGRAF48::GenusModel &model) const
{
	auto *tiereModel = model.mutable_tiere();
	if (tiereModel != nullptr)
	{
		const auto &testItems = m_tests.at(0).items();

		tiereModel->set_tiger(testItems[0].isChecked());
		tiereModel->set_baer(testItems[1].isChecked());
		tiereModel->set_katze(testItems[2].isChecked());
		tiereModel->set_pferd(testItems[3].isChecked());
		tiereModel->set_gans(testItems[4].isChecked());
		tiereModel->set_elefant(testItems[5].isChecked());
		tiereModel->set_affe(testItems[6].isChecked());
		tiereModel->set_hund(testItems[7].isChecked());
	}

	auto *futterModel = model.mutable_futter();
	if (futterModel != nullptr)
	{
		const auto &testItems = m_tests.at(1).items();

		futterModel->set_salat(testItems[0].isChecked());
		futterModel->set_fleisch(testItems[1].isChecked());
		futterModel->set_knochen(testItems[2].isChecked());
		futterModel->set_banane(testItems[3].isChecked());
		futterModel->set_apfel(testItems[4].isChecked());
		futterModel->set_karotte(testItems[5].isChecked());
		futterModel->set_honig(testItems[6].isChecked());
		futterModel->set_zucker(testItems[7].isChecked());
	}

	auto *zirkusModel = model.mutable_zirkus();
	if (zirkusModel != nullptr)
	{
		const auto &testItems = m_tests.at(2).items();

		zirkusModel->set_kiste(testItems[0].isChecked());
		zirkusModel->set_holz(testItems[1].isChecked());
		zirkusModel->set_vorhang(testItems[2].isChecked());
		zirkusModel->set_baum(testItems[3].isChecked());
	}
}
