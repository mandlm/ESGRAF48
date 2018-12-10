#include "LateSkillsModel.h"

#include <QTextTable>

#include <regex>

LateSkillsModel::LateSkillsModel(QObject *parent)
    : CheckableTestModel(parent)
{
}

void LateSkillsModel::printTableTo(QTextCursor &cursor) const
{
	QTextTableFormat tableFormat;
	tableFormat.setCellPadding(2);
	tableFormat.setCellSpacing(0);

	tableFormat.setColumnWidthConstraints({QTextLength(QTextLength::PercentageLength, 20),
	                                       QTextLength(QTextLength::PercentageLength, 5),
	                                       QTextLength(QTextLength::PercentageLength, 5),
	                                       QTextLength(QTextLength::PercentageLength, 5),
	                                       QTextLength(QTextLength::PercentageLength, 5),
	                                       QTextLength(QTextLength::PercentageLength, 5),
	                                       QTextLength(QTextLength::PercentageLength, 5),
	                                       QTextLength(QTextLength::PercentageLength, 5),
	                                       QTextLength(QTextLength::PercentageLength, 5),
	                                       QTextLength(QTextLength::PercentageLength, 5),
	                                       QTextLength(QTextLength::PercentageLength, 5),
	                                       QTextLength(QTextLength::PercentageLength, 26),
	                                       QTextLength(QTextLength::PercentageLength, 1),
	                                       QTextLength(QTextLength::PercentageLength, 3)});

	QTextTable *table = cursor.insertTable(m_tests.size() * 3, 14, tableFormat);

	int currentRow = 0;
	for (const auto &test : m_tests)
	{
		table->mergeCells(currentRow, 0, 3, 1);

		int currentColumn = 0;

		setCellText(*table, currentRow, currentColumn, test.name());
		currentColumn++;

		for (auto it = std::begin(test.items()); it != std::end(test.items()); std::advance(it, 2))
		{
			const auto &item = *it;
			const auto &nextItem = *std::next(it);

			table->mergeCells(currentRow, currentColumn, 1, 2);

			auto itemName = std::regex_replace(item.getText(), std::regex(R"((\S+).*)"), "$1");

			setCellText(*table, currentRow, currentColumn, itemName.c_str());
			setCellText(*table, currentRow + 1, currentColumn, "1");
			setCellText(*table, currentRow + 1, currentColumn + 1, "2");
			setCellChecked(*table, currentRow + 2, currentColumn, item.isChecked());
			setCellChecked(*table, currentRow + 2, currentColumn + 1, nextItem.isChecked());

			currentColumn += 2;
		}

		setCellNumber(*table, currentRow + 2, 13, test.getPoints());

		currentRow += 3;
	}
}
