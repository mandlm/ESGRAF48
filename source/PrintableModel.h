#pragma once

#include <QTextTableFormat>
#include <QTextTable>

class PrintableModel
{
public:
	virtual void printTo(QTextCursor &cursor) const = 0;

protected:
	static QTextTableFormat defaultTableFormat();

	static void setCellText(QTextTable &table, int row, int column, const QString &text);
	static void setCellChecked(QTextTable &table, int row, int column, bool check);
	static void setCellBackground(QTextTable &table, int row, int column, const QColor &color);

	template<typename NumberType>
	static void setCellNumber(QTextTable &table, int row, int column, const NumberType &number)
	{
		setCellText(table, row, column, QString::number(number));
	}
};
