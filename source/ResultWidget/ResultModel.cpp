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
	return 3;
}

int ResultModel::columnCount(const QModelIndex &parent) const
{
	return 9;
}

QVariant ResultModel::data(const QModelIndex &index, int role) const
{
	if (role == Qt::DisplayRole)
	{
		if (index.column() < m_results.size())
		{
			size_t points = m_results[index.column()].points();
			if (points != 0)
			{
				return static_cast<uint>(points);
			}
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
					return ">= PR 84";
				case 1:
					return "< PR 84";
				case 2:
					return "<= PR 16";
				default:
					return {};
			}
		default:
			return {};
	}
}

void ResultModel::setAge(const QDate &age)
{
	m_age = age;
}

void ResultModel::setPluralResult(size_t points)
{
	if (m_results[8].points() != points)
	{
		m_results[8] = points;
		emit dataChanged(index(0, 8), index(2, 8));
	}
}
