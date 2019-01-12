#pragma once

#include <QPainter>

class PrintableModel
{
public:
	virtual void printTo(QPainter &painter) const = 0;

protected:
	static QFont h1Font();
	static QFont tableFont();
};
