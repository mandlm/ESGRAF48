#include "WFModel.h"

WFModel::WFModel(QObject *parent)
    : CheckableTestModel(parent)
{
	m_tests = {
	    {"W-Frage",
	     {"Affe", "Affe", "Affe", "Affe", "Schwein", "Schwein", "Schwein", "Schwein", "Gans",
	      "Gans", "Gans", "Gans"}},
	    {"Verbtrennung", {"", "Affe", "", "", "", "", "", "Schwein", "", "", "Gans", ""}},
	    {"SVK: /-st/",
	     {"Affe", "Affe", "Affe", "Affe", "Schwein", "Schwein", "Schwein", "Schwein", "Gans",
	      "Gans", "Gans", "Gans"}},
	};
}

unsigned int WFModel::getV2Points() const
{
	unsigned int points = 0;

	for (auto testIndex : {0, 1})
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

unsigned int WFModel::getSvkPoints() const
{
	unsigned int points = 0;

	for (auto testIndex : {2})
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

bool WFModel::isValidIndex(const QModelIndex &index) const
{
	if (index.row() == 1)
	{
		return index.column() == 1 || index.column() == 7 || index.column() == 10;
	}

	return CheckableTestModel::isValidIndex(index);
}

void WFModel::write(ESGRAF48::V2SvkModel &model) const
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
}

void WFModel::read(const ESGRAF48::V2SvkModel &model)
{
	auto readOneVal = [&](const ESGRAF48::V2SvkModel::OneEach &modelData, int testIndex) {
		auto &testItems = m_tests.at(testIndex).items();

		testItems[1].setState(modelData.affe());
		testItems[7].setState(modelData.schwein());
		testItems[10].setState(modelData.gans());
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

	emit dataChanged(index(0, 0), index(rowCount() - 1, columnCount() - 1));
}

void WFModel::printTo(QPainter &painter) const
{
	painter.setFont(h2Font());

	painter.drawText(
	    0, 0, "Subtest 1: Verbzweitstellungsregel (V2) und Subjekt-Verb-Kontrollregel (SVK)");

	painter.setFont(tableFont());
	painter.setPen(tablePen());

	auto width = painter.device()->width();
	auto height = 1.5 * painter.fontMetrics().lineSpacing();

	std::set<unsigned int> blockStarters = {0, 3, 5, 7};
	std::set<unsigned int> v2Tests = {0, 1, 3, 5, 7, 8};
	std::set<unsigned int> svkTests = {2, 4, 6, 9, 10};

	double x = 0;
	double y = 0;
	auto testIndex = 0;
	for (const auto &test : m_tests)
	{
		double rowHeaderWidth = 0.2 * width;
		double resultCellWidth = test.size() > 8 ? 0.05 * width : 0.1 * width;
		double rowHeight = height;

		if (blockStarters.find(testIndex) != blockStarters.end())
		{
			y += rowHeight;
			drawTextSquare(painter, {x, y, rowHeaderWidth, 2 * rowHeight}, test.name());
			x += rowHeaderWidth;

			std::vector<std::pair<std::string, unsigned int>> columnHeaders;
			for (const auto &item : test.items())
			{
				const auto &itemText = item.getText();
				if (!columnHeaders.empty() && columnHeaders.back().first == itemText)
				{
					columnHeaders.back().second++;
				}
				else
				{
					columnHeaders.emplace_back(itemText, 1);
				}
			}

			for (const auto &columnHeader : columnHeaders)
			{
				double cellWidth = columnHeader.second * resultCellWidth;
				drawTextSquare(painter, {x, y, cellWidth, rowHeight}, columnHeader.first.c_str());
				x += cellWidth;
			}
			x = rowHeaderWidth;
			y += rowHeight;
		}
		else
		{
			drawTextSquare(painter, {x, y, rowHeaderWidth, rowHeight}, test.name());
			x += rowHeaderWidth;
		}

		unsigned int emptyItemsStack = 0;
		for (const auto &item : test.items())
		{
			if (item.getText().empty())
			{
				emptyItemsStack++;
			}
			else
			{
				if (emptyItemsStack > 0)
				{
					drawGreySquare(painter, {x - emptyItemsStack * resultCellWidth, y,
					                         emptyItemsStack * resultCellWidth, rowHeight});
					emptyItemsStack = 0;
				}

				drawCheckSquare(painter, {x, y, resultCellWidth, rowHeight}, item.isChecked());
			}
			x += resultCellWidth;
		}
		if (emptyItemsStack > 0)
		{
			drawGreySquare(painter, {x - emptyItemsStack * resultCellWidth, y,
			                         emptyItemsStack * resultCellWidth, rowHeight});
			emptyItemsStack = 0;
		}

		if (v2Tests.find(testIndex) != v2Tests.end())
		{
			drawResultSquare(painter, y, false, test.getPoints());
		}

		if (svkTests.find(testIndex) != svkTests.end())
		{
			drawResultSquare(painter, y, true, test.getPoints());
		}

		x = 0;
		y += rowHeight;

		testIndex++;
	}

	x = 0;
	y += height;

	painter.drawText(x, y, 0.85 * width, height, Qt::AlignRight | Qt::AlignVCenter,
	                 "Rohwertpunkte Total:");
	drawResultSquare(painter, y, false, getV2Points());
	drawResultSquare(painter, y, true, getSvkPoints());
}
