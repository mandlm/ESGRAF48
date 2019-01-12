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
	return QFont("Helvetica", 10);
}

QPen PrintableModel::tablePen()
{
	return QPen(Qt::black, 1, Qt::SolidLine);
}
