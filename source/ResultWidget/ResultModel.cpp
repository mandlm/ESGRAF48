#include "ResultModel.h"

#include <QDebug>

ResultModel::ResultModel(QObject *parent)
	: QAbstractTableModel(parent)
{
	m_results = { { "V2", "SVK", "VE", "Passiv", "Genus", "Akkusativ", "Dativ",
		"Genitiv", "Plural" } };
}

int ResultModel::rowCount(const QModelIndex &parent) const
{
	return 5;
}

int ResultModel::columnCount(const QModelIndex &parent) const
{
	return 9;
}

QVariant ResultModel::data(const QModelIndex &index, int role) const
{
	if (role == Qt::DisplayRole)
	{
		switch (index.row())
		{
			case 0:
				if (index.column() < m_results.size())
				{
					size_t points = m_results[index.column()].points();
					if (points != 0)
					{
						return static_cast<uint>(points);
					}
				}
			default:
				break;
		}

		return "-";
	}

	return {};
}

QVariant ResultModel::headerData(
	int section, Qt::Orientation orientation, int role) const
{
	if (role != Qt::DisplayRole)
	{
		return {};
	}

	switch (orientation)
	{
		case Qt::Horizontal:
			if (m_results.size() > section)
			{
				return m_results[section].name();
			}
		case Qt::Vertical:
			switch (section)
			{
				case 0:
					return "RP";
				case 1:
					return ">= PR 84";
				case 2:
					return "< PR 84";
				case 3:
					return "<= PR 16";
				case 4:
					return "T-Wert";
				default:
					return {};
			}
		default:
			return {};
	}
}

void ResultModel::setAge(const Age &age)
{
	qDebug() << "Age:" << age.years() << "years" << age.months() << "months";
	m_age = age;
}

void ResultModel::setPluralResult(size_t points)
{
	if (m_results[8].points() != points)
	{
		m_results[8] = points;
		emit dataChanged(index(0, 8), index(4, 8));
	}
}
