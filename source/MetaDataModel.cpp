#include "MetaDataModel.h"

#include <QDebug>

MetaDataModel::MetaDataModel(QObject *parent) : QAbstractTableModel(parent)
{
}

int MetaDataModel::rowCount(const QModelIndex &parent) const
{
	return 1;
}

int MetaDataModel::columnCount(const QModelIndex &parent) const
{
	return 5;
}

QVariant MetaDataModel::data(const QModelIndex &index, int role) const
{
	if (role == Qt::DisplayRole || role == Qt::EditRole)
	{
		switch (index.column())
		{
			case 0:
				return m_participant;
			case 1:
				return m_instructor;
			case 2:
				return m_dateOfBirth;
			case 3:
				return m_dateOfTest;
			case 4:
				return m_remarks;
			default:
				return QVariant();
		}
	}

	return QVariant();
}
