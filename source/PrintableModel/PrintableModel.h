#pragma once

#include "CheckableTestModel.h"

#include <QPainter>
#include <QFont>
#include <QPen>
#include <QRect>
#include <QString>

class PrintableModel : public CheckableTestModel
{
	Q_OBJECT

public:
	PrintableModel(QObject *parent);

	virtual void printTo(QPainter &painter) const;

	static QFont h1Font();
	static QFont h2Font();
	static QFont tableFont();

	static QPen tablePen();
	static QPen resultPen();

	static double headerWidthFactor();
	static double cellWidthFactor();

	static void drawTextSquare(QPainter &painter, const QRectF &cell, const QString &text);
	static void drawNumberSquare(QPainter &painter, double x, double y, int number);
	static void drawCheckSquare(QPainter &painter, const QRectF &cell, bool checked);
	static void drawResultSquare(QPainter &painter, double y, bool rightCell, unsigned int value);
	static void drawGreySquare(QPainter &painter, const QRectF &cell);

	static void drawHeader2(QPainter &painter, const QString &text);

protected:
	virtual void printHeader(QPainter &painter) const;
	virtual void printTests(QPainter &painter) const;
	virtual void printSummary(QPainter &painter) const;
};
