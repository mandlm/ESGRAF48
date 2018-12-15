#pragma once

#include <QTextTableFormat>

class PrintableModel
{
public:
	virtual void printTo(QTextCursor &cursor) const = 0;

protected:
	static QTextTableFormat defaultTableFormat();
};
