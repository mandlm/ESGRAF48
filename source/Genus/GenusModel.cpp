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
        if (index.row() == 0 && m_tiere.find(index.column()) != m_tiere.end())
        {
            return m_tiere.find(index.column())->second.getText().c_str();
        }

		return "Hello";
	}

	if (role == Qt::CheckStateRole)
	{
        if (index.row() == 0 && m_tiere.find(index.column()) != m_tiere.end())
        {
            return m_tiere.find(index.column())->second.isChecked() ? Qt::Checked : Qt::Unchecked;
        }

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
    if (role != Qt::CheckStateRole)
	{
		return QAbstractTableModel::setData(index, value, role);
	}
    else
    {
        if (index.row() == 0 && m_tiere.find(index.column()) != m_tiere.end())
        {
            m_tiere.find(index.column())->second.setState(value.toBool());

            return true;
        }
    }

    return false;
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
