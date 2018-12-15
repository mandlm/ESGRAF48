#include "PrintableModel.h"

QTextTableFormat PrintableModel::defaultTableFormat()
{
	QTextTableFormat tableFormat;
	tableFormat.setCellPadding(2);
	tableFormat.setCellSpacing(0);

	return tableFormat;
}

void PrintableModel::setCellText(QTextTable &table, int row, int column, const QString &text)
{
	auto cell = table.cellAt(row, column);
	auto textCursor = cell.firstCursorPosition();

	auto blockFormat = textCursor.blockFormat();
	blockFormat.setAlignment(Qt::AlignCenter);
	textCursor.setBlockFormat(blockFormat);

	auto cellFormat = cell.format();
	cellFormat.setVerticalAlignment(QTextCharFormat::AlignMiddle);
	cell.setFormat(cellFormat);

	auto charFormat = textCursor.charFormat();
	charFormat.setVerticalAlignment(QTextCharFormat::AlignMiddle);
	charFormat.setFontPointSize(8);
	textCursor.setCharFormat(charFormat);

	textCursor.insertText(text);
}

void PrintableModel::setCellChecked(QTextTable &table, int row, int column, bool check)
{
	setCellText(table, row, column, check ? "x" : "\u2610");
}

void PrintableModel::setCellBackground(QTextTable &table, int row, int column, const QColor &color)
{
	auto cell = table.cellAt(row, column);

	auto cellFormat = cell.format();
	cellFormat.setBackground(QBrush(color));
	cell.setFormat(cellFormat);
}

