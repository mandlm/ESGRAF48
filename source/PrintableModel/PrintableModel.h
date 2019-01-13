#pragma once

#include <QPainter>
#include <QFont>
#include <QPen>
#include <QRect>
#include <QString>

class PrintableModel
{
public:
	virtual void printTo(QPainter &painter) const = 0;

protected:
	static QFont h1Font();
	static QFont h2Font();
	static QFont tableFont();

	static QPen tablePen();

	static void drawTextSquare(QPainter &painter, const QRectF &cell, const QString &text);
	static void drawCheckSquare(QPainter &painter, const QRectF &cell, bool checked);
	static void drawResultSquare(QPainter &painter, double y, bool rightCell, unsigned int value);
	static void drawGreySquare(QPainter &painter, const QRectF &cell);
};
