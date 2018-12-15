#include "PrintableModel.h"

QTextTableFormat PrintableModel::defaultTableFormat()
{
	QTextTableFormat tableFormat;
	tableFormat.setCellPadding(2);
	tableFormat.setCellSpacing(0);

	return tableFormat;
}

