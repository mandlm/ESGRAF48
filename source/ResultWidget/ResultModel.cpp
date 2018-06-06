#include "ResultModel.h"

#include <QDebug>

ResultModel::ResultModel(QObject *parent)
	: QAbstractTableModel(parent)
{
	m_results = {{ "V2", "SVK", "VE", "Passiv", "Genus", "Akkusativ", "Dativ", "Genitiv", "Plural" }};
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
		return "data";
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
