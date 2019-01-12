#include "V2SvkModel.h"

V2SvkModel::V2SvkModel(QObject *parent)
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

unsigned int V2SvkModel::getV2Points()
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

unsigned int V2SvkModel::getSvkPoints()
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

void V2SvkModel::printTo(QPainter &painter) const
{
	painter.setFont(h2Font());

	painter.drawText(
	    0, 0, "Subtest 1: Verbzweitstellungsregel (V2) und Subjekt-Verb-Kontrollregel (SVK)");

	painter.translate(0, 1.5 * painter.fontMetrics().lineSpacing());

	painter.setFont(tableFont());
	painter.setPen(tablePen());

	auto width = painter.device()->width();
	auto height = 1.5 * painter.fontMetrics().lineSpacing();

	auto drawTextSquare = [&](double left, double top, double width, double height,
	                          const QString &text) {
		painter.drawText(left, top, width, height, Qt::AlignCenter, text);
		painter.drawLine(left, top, left + width, top);
		painter.drawLine(left + width, top, left + width, top + height);
		painter.drawLine(left + width, top + height, left, top + height);
		painter.drawLine(left, top + height, left, top);
	};

	auto drawCheckSquare = [&](double left, double top, double width, double height, bool checked) {
		drawTextSquare(left, top, width, height, checked ? "\u2612" : "\u2610");
	};

	auto drawResultSquare = [&](bool right, bool bold, unsigned int value, double y) {
		double cellWidth = 0.03 * width;
		double x = width - cellWidth - (right ? 0 : 0.04 * width);

		drawTextSquare(x, y, cellWidth, height, QString::number(value));
	};

	auto drawGreySquare = [&](double left, double top, double width, double height) {
		auto prevBrush = painter.brush();

		painter.setBrush(QBrush(QColor(224, 224, 224)));
		painter.drawRect(left, top, width, height);
		
		painter.setBrush(prevBrush);
	};

	auto x = 0.0;
	auto y = 0.0;
	auto cellWidth = 0.2 * width;
	drawTextSquare(x, y, cellWidth, 2 * height, "W-Fragen");
	x += cellWidth;
	drawTextSquare(x, y, cellWidth, height, "Affe");
	x += cellWidth;
	drawTextSquare(x, y, cellWidth, height, "Schwein");
	x += cellWidth;
	drawTextSquare(x, y, cellWidth, height, "Gans");

	x = 0.2 * width;
	y += height;
	cellWidth = 0.05 * width;
	for (int i = 0; i < 12; ++i)
	{
		drawCheckSquare(x, y, cellWidth, height, true);
		x += cellWidth;
	}
	drawResultSquare(false, false, 9, y);

	x = 0;
	y += height;
	cellWidth = 0.2 * width;
	drawTextSquare(x, y, cellWidth, height, "Verbtrennung");
	x += cellWidth;
	cellWidth = 0.05 * width;
	drawGreySquare(x, y, cellWidth, height);
	x += cellWidth;
	drawCheckSquare(x, y, cellWidth, height, true);
	x += cellWidth;
	drawGreySquare(x, y, 5 * cellWidth, height);
	x += 5 * cellWidth;
	drawCheckSquare(x, y, cellWidth, height, true);
	x += cellWidth;
	drawGreySquare(x, y, 2 * cellWidth, height);
	x += 2 * cellWidth;
	drawCheckSquare(x, y, cellWidth, height, true);
	x += cellWidth;
	drawGreySquare(x, y, cellWidth, height);
	x += cellWidth;
	drawResultSquare(false, false, 2, y);

	x = 0;
	y += height;
	cellWidth = 0.2 * width;
	drawTextSquare(x, y, cellWidth, height, "SVK: /-st/");
	x += cellWidth;
	cellWidth = 0.05 * width;
	for (int i = 0; i < 12; ++i)
	{
		drawCheckSquare(x, y, cellWidth, height, true);
		x += cellWidth;
	}
	drawResultSquare(true, false, 8, y);
}
