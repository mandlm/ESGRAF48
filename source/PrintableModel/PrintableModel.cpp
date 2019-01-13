#include "PrintableModel.h"

QFont PrintableModel::h1Font()
{
	return QFont("Helvetica", 16);
}

QFont PrintableModel::h2Font()
{
	return QFont("Helvetica", 12);
}

QFont PrintableModel::tableFont()
{
	return QFont("Helvetica", 8);
}

QPen PrintableModel::tablePen()
{
	return QPen(Qt::black, 1, Qt::SolidLine);
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

void PrintableModel::PrintableModel::drawCheckSquare(QPainter &painter, const QRectF &cell,
                                                     bool checked)
{
	drawTextSquare(painter, cell, checked ? "\u2612" : "\u2610");
}

void PrintableModel::drawResultSquare(QPainter &painter, double y, bool rightCell,
                                      unsigned int value)
{
	auto prevPen = painter.pen();
	painter.setPen(tablePen());

	double pageWidth = painter.device()->width();
	double cellWidth = 0.03 * pageWidth;
	double cellHeight = painter.fontMetrics().lineSpacing();
	double x = pageWidth - cellWidth - (rightCell ? 0 : 0.04 * pageWidth);

	drawTextSquare(painter, {x, y, cellWidth, cellHeight}, QString::number(value));

	painter.setPen(prevPen);
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
