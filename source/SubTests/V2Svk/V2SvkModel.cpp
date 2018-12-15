#include "V2SvkModel.h"

#include <QTextTable>

V2SvkModel::V2SvkModel(QObject *parent)
    : CheckableTestModel(parent)
{
	m_tests = {
	    {"W-Fragen",
	     {"Affe", "Affe", "Affe", "Affe", "Schwein", "Schwein", "Schwein", "Schwein", "Gans",
	      "Gans", "Gans", "Gans"}},
	    {"Verbtrennung", {"", "Affe", "", "", "", "", "", "Schwein", "", "", "Gans", ""}},
	    {"SVK: /-st/",
	     {"Affe", "Affe", "Affe", "Affe", "Schwein", "Schwein", "Schwein", "Schwein", "Gans",
	      "Gans", "Gans", "Gans"}},

	    {"Objekt-Topikalisierung",
	     {"Affe", "Affe", "Affe", "Affe", "Schwein", "Schwein", "Schwein", "Schwein", "Gans",
	      "Gans", "Gans", "Gans"}},
	    {"SVK: Stamm",
	     {"Affe", "Affe", "Affe", "Affe", "Schwein", "Schwein", "Schwein", "Schwein", "Gans",
	      "Gans", "Gans", "Gans"}},

	    {"Temporaladverb Präsens", {"Affe", "Affe", "Schwein", "Schwein", "Gans", "Gans"}},
	    {"SKV: /-e/ o. Stamm", {"Affe", "Affe", "Schwein", "Schwein", "Gans", "Gans"}},

	    {"Temporaladverb Perfekt", {"Affe", "Affe", "Schwein", "Schwein", "Gans", "Gans"}},
	    {"Verbtrennung", {"Affe", "Affe", "Schwein", "Schwein", "Gans", "Gans"}},
	    {"SVK: /-e/ o. Stamm", {"Affe", "Affe", "Schwein", "Schwein", "Gans", "Gans"}},
	    {"Partizip", {"Affe", "Affe", "Schwein", "Schwein", "Gans", "Gans"}},
	};
}

unsigned int V2SvkModel::getV2Points() const
{
	unsigned int points = 0;

	for (auto testIndex : {0, 1, 3, 5, 7, 8})
	{
		const auto &test = m_tests.at(testIndex);

		for (const auto &item : test.items())
		{
			if (item.isChecked())
			{
				points++;
			}
		}
	}

	return points;
}

unsigned int V2SvkModel::getSvkPoints() const
{
	unsigned int points = 0;

	for (auto testIndex : {2, 4, 6, 9, 10})
	{
		const auto &test = m_tests.at(testIndex);

		for (const auto &item : test.items())
		{
			if (item.isChecked())
			{
				points++;
			}
		}
	}

	return points;
}

bool V2SvkModel::isValidIndex(const QModelIndex &index) const
{
	switch (index.row())
	{
		case 1:
			return index.column() == 1 || index.column() == 7 || index.column() == 10;
		case 5:
		case 6:
		case 7:
		case 8:
		case 9:
		case 10:
			return index.column() < 6;
		default:
			return CheckableTestModel::isValidIndex(index);
	}
}

void V2SvkModel::write(ESGRAF48::V2SvkModel &model) const
{
	auto writeOneVal = [&](ESGRAF48::V2SvkModel::OneEach *modelData, int testIndex) {
		if (modelData != nullptr)
		{
			const auto &testItems = m_tests.at(testIndex).items();

			modelData->set_affe(testItems[1].isChecked());
			modelData->set_schwein(testItems[7].isChecked());
			modelData->set_gans(testItems[10].isChecked());
		}
	};

	auto writeTwoVals = [&](ESGRAF48::V2SvkModel::TwoEach *modelData, int testIndex) {
		if (modelData != nullptr)
		{
			const auto &testItems = m_tests.at(testIndex).items();

			modelData->set_affe1(testItems[0].isChecked());
			modelData->set_affe2(testItems[1].isChecked());
			modelData->set_schwein1(testItems[2].isChecked());
			modelData->set_schwein2(testItems[3].isChecked());
			modelData->set_gans1(testItems[4].isChecked());
			modelData->set_gans2(testItems[5].isChecked());
		}
	};

	auto writeFourVals = [&](ESGRAF48::V2SvkModel::FourEach *modelData, int testIndex) {
		if (modelData != nullptr)
		{
			const auto &testItems = m_tests.at(testIndex).items();

			modelData->set_affe1(testItems[0].isChecked());
			modelData->set_affe2(testItems[1].isChecked());
			modelData->set_affe3(testItems[2].isChecked());
			modelData->set_affe4(testItems[3].isChecked());
			modelData->set_schwein1(testItems[4].isChecked());
			modelData->set_schwein2(testItems[5].isChecked());
			modelData->set_schwein3(testItems[6].isChecked());
			modelData->set_schwein4(testItems[7].isChecked());
			modelData->set_gans1(testItems[8].isChecked());
			modelData->set_gans2(testItems[9].isChecked());
			modelData->set_gans3(testItems[10].isChecked());
			modelData->set_gans4(testItems[11].isChecked());
		}
	};

	writeFourVals(model.mutable_wfrage(), 0);
	writeOneVal(model.mutable_verbtrennung1(), 1);
	writeFourVals(model.mutable_svkst(), 2);
	writeFourVals(model.mutable_objtop(), 3);
	writeFourVals(model.mutable_svkstamm(), 4);
	writeTwoVals(model.mutable_temppraes(), 5);
	writeTwoVals(model.mutable_svke1(), 6);
	writeTwoVals(model.mutable_tempperf(), 7);
	writeTwoVals(model.mutable_verbtrennung2(), 8);
	writeTwoVals(model.mutable_svke2(), 9);
	writeTwoVals(model.mutable_partizip(), 10);
}

void V2SvkModel::read(const ESGRAF48::V2SvkModel &model)
{
	auto readOneVal = [&](const ESGRAF48::V2SvkModel::OneEach &modelData, int testIndex) {
		auto &testItems = m_tests.at(testIndex).items();

		testItems[1].setState(modelData.affe());
		testItems[7].setState(modelData.schwein());
		testItems[10].setState(modelData.gans());
	};

	auto readTwoVals = [&](const ESGRAF48::V2SvkModel::TwoEach &modelData, int testIndex) {
		auto &testItems = m_tests.at(testIndex).items();

		testItems[0].setState(modelData.affe1());
		testItems[1].setState(modelData.affe2());
		testItems[2].setState(modelData.schwein1());
		testItems[3].setState(modelData.schwein2());
		testItems[4].setState(modelData.gans1());
		testItems[5].setState(modelData.gans2());
	};

	auto readFourVals = [&](const ESGRAF48::V2SvkModel::FourEach &modelData, int testIndex) {
		auto &testItems = m_tests.at(testIndex).items();

		testItems[0].setState(modelData.affe1());
		testItems[1].setState(modelData.affe2());
		testItems[2].setState(modelData.affe3());
		testItems[3].setState(modelData.affe4());
		testItems[4].setState(modelData.schwein1());
		testItems[5].setState(modelData.schwein2());
		testItems[6].setState(modelData.schwein3());
		testItems[7].setState(modelData.schwein4());
		testItems[8].setState(modelData.gans1());
		testItems[9].setState(modelData.gans2());
		testItems[10].setState(modelData.gans3());
		testItems[11].setState(modelData.gans4());
	};

	readFourVals(model.wfrage(), 0);
	readOneVal(model.verbtrennung1(), 1);
	readFourVals(model.svkst(), 2);
	readFourVals(model.objtop(), 3);
	readFourVals(model.svkstamm(), 4);
	readTwoVals(model.temppraes(), 5);
	readTwoVals(model.svke1(), 6);
	readTwoVals(model.tempperf(), 7);
	readTwoVals(model.verbtrennung2(), 8);
	readTwoVals(model.svke2(), 9);
	readTwoVals(model.partizip(), 10);

	emit dataChanged(index(0, 0), index(rowCount() - 1, columnCount() - 1));
}

std::string V2SvkModel::getName() const
{
	return "Subtest 1: Verbzweitstellungsregel (V2) und Subjekt-Verb-Kontrollregel (SVK)";
}

void V2SvkModel::printTableTo(QTextCursor &cursor) const
{
	QTextTableFormat tableFormat12 = defaultTableFormat();

	tableFormat12.setColumnWidthConstraints({QTextLength(QTextLength::PercentageLength, 20),
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
	                                         QTextLength(QTextLength::PercentageLength, 5),
	                                         QTextLength(QTextLength::PercentageLength, 5),
	                                         QTextLength(QTextLength::PercentageLength, 13),
	                                         QTextLength(QTextLength::PercentageLength, 3),
	                                         QTextLength(QTextLength::PercentageLength, 1),
	                                         QTextLength(QTextLength::PercentageLength, 3)});

	QTextTableFormat tableFormat6 = defaultTableFormat();

	tableFormat6.setColumnWidthConstraints({QTextLength(QTextLength::PercentageLength, 20),
	                                        QTextLength(QTextLength::PercentageLength, 10),
	                                        QTextLength(QTextLength::PercentageLength, 10),
	                                        QTextLength(QTextLength::PercentageLength, 10),
	                                        QTextLength(QTextLength::PercentageLength, 10),
	                                        QTextLength(QTextLength::PercentageLength, 10),
	                                        QTextLength(QTextLength::PercentageLength, 10),
	                                        QTextLength(QTextLength::PercentageLength, 13),
	                                        QTextLength(QTextLength::PercentageLength, 3),
	                                        QTextLength(QTextLength::PercentageLength, 1),
	                                        QTextLength(QTextLength::PercentageLength, 3)});

	auto writeHeader = [](QTextTable *table, const CheckableTest &test, int colSpan) {
		table->mergeCells(0, 0, 2, 1);

		int column = 1;

		for (auto it = std::begin(test.items()); it != std::end(test.items());
		     std::advance(it, colSpan))
		{
			table->mergeCells(0, column, 1, colSpan);
			setCellText(*table, 0, column, it->getText().c_str());

			column += colSpan;
		}
	};

	auto writeLine = [](QTextTable *table, const CheckableTest &test, int row, int resultColumn) {
		int column = 0;

		setCellText(*table, row, column, test.name());
		for (const auto item : test.items())
		{
			column++;

			if (!item.getText().empty())
			{
				setCellChecked(*table, row, column, item.isChecked());
			}
		}

		setCellNumber(*table, row, resultColumn, test.getPoints());
	};

	{
		QTextTable *table = cursor.insertTable(4, 17, tableFormat12);

		writeHeader(table, m_tests[0], 4);
		writeLine(table, m_tests[0], 1, 14);
		writeLine(table, m_tests[1], 2, 14);
		writeLine(table, m_tests[2], 3, 16);
	}

	cursor.movePosition(QTextCursor::End);
	cursor.insertBlock();
	cursor.insertText("\n");

	{
		QTextTable *table = cursor.insertTable(3, 17, tableFormat12);

		writeHeader(table, m_tests[3], 4);
		writeLine(table, m_tests[3], 1, 14);
		writeLine(table, m_tests[4], 2, 16);
	}

	cursor.movePosition(QTextCursor::End);
	cursor.insertBlock();
	cursor.insertText("\n");

	{
		QTextTable *table = cursor.insertTable(3, 11, tableFormat6);

		writeHeader(table, m_tests[5], 2);
		writeLine(table, m_tests[5], 1, 8);
		writeLine(table, m_tests[6], 2, 10);
	}

	cursor.movePosition(QTextCursor::End);
	cursor.insertBlock();
	cursor.insertText("\n");

	{
		QTextTable *table = cursor.insertTable(5, 11, tableFormat6);

		writeHeader(table, m_tests[7], 2);
		writeLine(table, m_tests[7], 1, 8);
		writeLine(table, m_tests[8], 2, 8);
		writeLine(table, m_tests[9], 3, 10);
		writeLine(table, m_tests[10], 4, 10);
	}
}

void V2SvkModel::printSummaryTo(QTextCursor &cursor) const
{
	QTextTableFormat tableFormat = defaultTableFormat();

	tableFormat.setColumnWidthConstraints({QTextLength(QTextLength::PercentageLength, 72),
	                                       QTextLength(QTextLength::PercentageLength, 20),
	                                       QTextLength(QTextLength::PercentageLength, 1),
	                                       QTextLength(QTextLength::PercentageLength, 3),
	                                       QTextLength(QTextLength::PercentageLength, 1),
	                                       QTextLength(QTextLength::PercentageLength, 3)});

	QTextTable *table = cursor.insertTable(1, 6, tableFormat);

	setCellText(*table, 0, 1, "Rohwertpunkte Total:");
	setCellNumber(*table, 0, 3, getV2Points());
	setCellNumber(*table, 0, 5, getSvkPoints());
}

