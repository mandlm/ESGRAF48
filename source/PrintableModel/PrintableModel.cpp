#include "PrintableModel.h"

#include <regex>

PrintableModel::PrintableModel(QObject *parent)
    : CheckableTestModel(parent)
{
}

void PrintableModel::printTo(QPainter &painter) const
{
	printHeader(painter);
	printTests(painter);
	printSummary(painter);
}

QFont PrintableModel::h1Font()
{
	return QFont("Helvetica", 16);
}

QFont PrintableModel::h2Font()
{
	return QFont("Helvetica", 10);
}

QFont PrintableModel::tableFont()
{
	return QFont("Helvetica", 8);
}

QPen PrintableModel::tablePen()
{
	return QPen(Qt::black, 1, Qt::SolidLine);
}

QPen PrintableModel::resultPen()
{
	return QPen(Qt::black, 2, Qt::SolidLine);
}

double PrintableModel::headerWidthFactor()
{
	return 0.17;
}

double PrintableModel::cellWidthFactor()
{
	return 0.085;
}

void PrintableModel::drawTextSquare(QPainter &painter, const QRectF &cell, const QString &text)
{
	auto prevPen = painter.pen();
	painter.setPen(tablePen());

	painter.drawText(cell, Qt::AlignCenter, text);

	painter.drawLine(cell.topLeft(), cell.topRight());
	painter.drawLine(cell.topRight(), cell.bottomRight());
	painter.drawLine(cell.bottomRight(), cell.bottomLeft());
	painter.drawLine(cell.bottomLeft(), cell.topLeft());

	painter.setPen(prevPen);
}

void PrintableModel::drawNumberSquare(QPainter &painter, double x, double y, int number)
{
	QRectF cell = {x, y, 0.03 * painter.device()->width(),
	               1.5 * painter.fontMetrics().lineSpacing()};

	painter.drawText(cell, Qt::AlignCenter, QString::number(number));

	painter.drawLine(cell.topLeft(), cell.topRight());
	painter.drawLine(cell.topRight(), cell.bottomRight());
	painter.drawLine(cell.bottomRight(), cell.bottomLeft());
	painter.drawLine(cell.bottomLeft(), cell.topLeft());
}

void PrintableModel::PrintableModel::drawCheckSquare(QPainter &painter, const QRectF &cell,
                                                     bool checked)
{
	drawTextSquare(painter, cell, checked ? "\u2612" : "\u2610");
}

void PrintableModel::drawResultSquare(QPainter &painter, double y, bool rightCell,
                                      unsigned int value)
{
	double pageWidth = painter.device()->width();
	double cellWidth = 0.03 * pageWidth;
	double cellHeight = 1.5 * painter.fontMetrics().lineSpacing();
	double x = pageWidth - cellWidth - (rightCell ? 0 : 0.04 * pageWidth);

	drawTextSquare(painter, {x, y, cellWidth, cellHeight}, QString::number(value));
}

void PrintableModel::drawGreySquare(QPainter &painter, const QRectF &cell)
{
	auto prevBrush = painter.brush();
	auto prevPen = painter.pen();

	painter.setBrush(QBrush(QColor(224, 224, 224)));
	painter.setPen(QPen(Qt::NoPen));
	QPointF points[4] = {cell.topLeft(), cell.topRight(), cell.bottomRight(), cell.bottomLeft()};
	painter.drawPolygon(points, 4);

	painter.setPen(tablePen());
	painter.drawLine(cell.topLeft(), cell.topRight());
	painter.drawLine(cell.topRight(), cell.bottomRight());
	painter.drawLine(cell.bottomRight(), cell.bottomLeft());
	painter.drawLine(cell.bottomLeft(), cell.topLeft());

	painter.setBrush(prevBrush);
	painter.setPen(prevPen);
}

void PrintableModel::drawHeader2(QPainter &painter, const QString &text)
{
	painter.setFont(h2Font());
	painter.drawText(0, 0, text);
	painter.translate(0, 0.5 * painter.fontMetrics().lineSpacing());
}

void PrintableModel::printHeader(QPainter &painter) const
{
	auto title = getTitle();
	if (!title.isEmpty())
	{
		drawHeader2(painter, getTitle());
	}
}

void PrintableModel::printTests(QPainter &painter) const
{
	painter.setFont(tableFont());
	painter.setPen(tablePen());

	auto width = painter.device()->width();
	auto height = 1.5 * painter.fontMetrics().lineSpacing();

	double headerWidth = headerWidthFactor() * width;
	double cellWidth = cellWidthFactor() * width;
	double rowHeight = height;

	double x = 0;
	double y = 0;
	for (const auto &test : m_tests)
	{
		QString testName = QString::fromStdString(
		    std::regex_replace(test.name().toStdString(), std::regex("\\s"), "\n"));

		drawTextSquare(painter, {0, y, headerWidth, 2 * rowHeight}, testName);
		x = headerWidth;

		for (const auto &item : test.items())
		{
			drawTextSquare(painter, {x, y, cellWidth, rowHeight}, item.getText().c_str());
			drawCheckSquare(painter, {x, y + rowHeight, cellWidth, rowHeight}, item.isChecked());

			x += cellWidth;
		}
		y += rowHeight;

		drawResultSquare(painter, y, true, test.getPoints());
		y += rowHeight;
	}

	painter.translate(0, y + rowHeight);
}

void PrintableModel::printSummary(QPainter &painter) const
{
	painter.setFont(tableFont());

	auto width = painter.device()->width();
	auto height = 1.5 * painter.fontMetrics().lineSpacing();

	painter.drawText(0, 0, 0.95 * width, height, Qt::AlignRight | Qt::AlignVCenter,
	                 "Rohwertpunkte Total:");
	painter.setPen(resultPen());
	drawNumberSquare(painter, 0.97 * width, 0, getPoints());

	painter.translate(0, 3 * height);
}
