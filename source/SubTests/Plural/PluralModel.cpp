#include "PluralModel.h"

#include <QSize>

PluralModel::PluralModel(QObject *parent)
    : CheckableTestModel(parent)
{
	m_tests = {{"",
	            {"Fisch /-e/", "Banane /-n/", "Bonbon /-s/", "Ei /-er/", "Eimer /-ø/",
	             "Korn UML+/-er/", "Nuss UML+/-e/", "Bär /-en/", "Apfel UML"}}};
}

QVariant PluralModel::data(const QModelIndex &index, int role) const
{
	if (role == Qt::SizeHintRole)
	{
		return QSize(180, 0);
	}

	return CheckableTestModel::data(index, role);
}

void PluralModel::read(const ESGRAF48::PluralModel &model)
{
	auto &testItems = m_tests.at(0).items();

	testItems[0].setState(model.fisch());
	testItems[1].setState(model.banane());
	testItems[2].setState(model.bonbon());
	testItems[3].setState(model.ei());
	testItems[4].setState(model.eimer());
	testItems[5].setState(model.korn());
	testItems[6].setState(model.nuss());
	testItems[7].setState(model.baer());
	testItems[8].setState(model.apfel());
}

void PluralModel::write(ESGRAF48::PluralModel &model) const
{
	const auto &testItems = m_tests.at(0).items();

	model.set_fisch(testItems[0].isChecked());
	model.set_banane(testItems[1].isChecked());
	model.set_bonbon(testItems[2].isChecked());
	model.set_ei(testItems[3].isChecked());
	model.set_eimer(testItems[4].isChecked());
	model.set_korn(testItems[5].isChecked());
	model.set_nuss(testItems[6].isChecked());
	model.set_baer(testItems[7].isChecked());
	model.set_apfel(testItems[8].isChecked());
}
