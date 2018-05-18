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

Qt::ItemFlags MetaDataModel::flags(const QModelIndex &index) const
{
	return QAbstractTableModel::flags(index) | Qt::ItemIsEditable;
}

bool MetaDataModel::setData(
	const QModelIndex &index, const QVariant &value, int role)
{
	if (role != Qt::EditRole)
	{
		return QAbstractTableModel::setData(index, value, role);
	}

	bool valueChanged = false;

	switch (index.column())
	{
		case 0:
			if (value.toString() != m_participant)
			{
				m_participant = value.toString();
				valueChanged = true;
			}
			break;
		case 1:
			if (value.toString() != m_instructor)
			{
				m_instructor = value.toString();
				valueChanged = true;
			}
			break;
		case 2:
			if (value.toDate() != m_dateOfBirth)
			{
				m_dateOfBirth = value.toDate();
				valueChanged = true;
			}
			break;
		case 3:
			if (value.toDate() != m_dateOfTest)
			{
				m_dateOfTest = value.toDate();
				valueChanged = true;
			}
			break;
		case 4:
			if (value.toString() != m_remarks)
			{
				m_remarks = value.toString();
				valueChanged = true;
			}
			break;
		default:
			break;
	}

	return valueChanged;
}

void MetaDataModel::write(QJsonObject &json) const
{
	json["participant name"] = m_participant;
	json["instructor name"] = m_instructor;
	json["date of birth"] = m_dateOfBirth.toString(Qt::ISODate);
	json["date of test"] = m_dateOfTest.toString(Qt::ISODate);
	json["remarks"] = m_remarks;
}

void MetaDataModel::read(const QJsonObject &json)
{
	const auto &participant = json["participant name"];
	if (participant.isString())
	{
		m_participant = participant.toString();
	}

	const auto &instructor = json["instructor name"];
	if (instructor.isString())
	{
		m_instructor = instructor.toString();
	}

	const auto &dateOfBirth = json["date of birth"];
	if (dateOfBirth.isString())
	{
		m_dateOfBirth = QDate::fromString(dateOfBirth.toString(), Qt::ISODate);
	}

	const auto &dateOfTest = json["date of test"];
	if (dateOfTest.isString())
	{
		m_dateOfTest = QDate::fromString(dateOfTest.toString(), Qt::ISODate);
	}

	const auto &remarks = json["remarks"];
	if (remarks.isString())
	{
		m_remarks = remarks.toString();
	}
}
