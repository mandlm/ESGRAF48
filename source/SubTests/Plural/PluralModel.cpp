#include "PluralModel.h"

#include <QSize>
#include <QTextTable>
#include <QDebug>

#include <regex>

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

	emit dataChanged(index(0, 0), index(rowCount() - 1, columnCount() - 1));
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

std::string PluralModel::getName() const
{
	return "Subtest 5: Plural";
}
	
void PluralModel::printTableTo(QTextCursor &cursor) const
{
	QTextTableFormat tableFormat = defaultTableFormat();

	tableFormat.setColumnWidthConstraints({QTextLength(QTextLength::PercentageLength, 10),
	                                       QTextLength(QTextLength::PercentageLength, 10),
	                                       QTextLength(QTextLength::PercentageLength, 10),
	                                       QTextLength(QTextLength::PercentageLength, 10),
	                                       QTextLength(QTextLength::PercentageLength, 10),
	                                       QTextLength(QTextLength::PercentageLength, 10),
	                                       QTextLength(QTextLength::PercentageLength, 10),
	                                       QTextLength(QTextLength::PercentageLength, 10),
	                                       QTextLength(QTextLength::PercentageLength, 10),
	                                       QTextLength(QTextLength::PercentageLength, 10)});

	QTextTable *table = cursor.insertTable(2, 10, tableFormat);

	const auto &test = m_tests.front();
	
	int currentColumn = 0;
	for (const auto &item : test.items())
	{
		std::string itemName = std::regex_replace(item.getText(), std::regex("\\s"), "\n",
		                                          std::regex_constants::format_first_only);

		setCellText(*table, 0, currentColumn, itemName.c_str());
		setCellChecked(*table, 1, currentColumn, item.isChecked());

		currentColumn++;
	}
}

