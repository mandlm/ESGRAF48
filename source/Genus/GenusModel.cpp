#include "GenusModel.h"

GenusModel::GenusModel(QObject *parent)
	: QAbstractTableModel(parent)
{
}

int GenusModel::rowCount(const QModelIndex &parent) const
{
	return 3;
}

int GenusModel::columnCount(const QModelIndex &parent) const
{
	return 8;
}

QVariant GenusModel::data(const QModelIndex &index, int role) const
{
	if (role == Qt::DisplayRole)
	{
		return "Hello";
	}

	if (role == Qt::CheckStateRole)
	{
		return Qt::Unchecked;
	}

	return QVariant();
}

Qt::ItemFlags GenusModel::flags(const QModelIndex &index) const
{
	return QAbstractTableModel::flags(index) | Qt::ItemIsEnabled
		   | Qt::ItemIsUserCheckable;
}

bool GenusModel::setData(
	const QModelIndex &index, const QVariant &value, int role)
{
	if (role != Qt::EditRole)
	{
		return QAbstractTableModel::setData(index, value, role);
	}

	return true;
}

QVariant GenusModel::headerData(
	int section, Qt::Orientation orientation, int role) const
{
	if (role == Qt::DisplayRole)
	{
		if (orientation == Qt::Vertical)
		{
			switch (section)
			{
				case 0:
					return "Tiere";
				case 1:
					return "Futter";
				case 2:
					return "Zirkus";
				default:
					return {};
			}
		}
	}

	return {};
}

void GenusModel::write(QJsonObject &json) const
{
}

void GenusModel::read(const QJsonObject &json)
{
}
