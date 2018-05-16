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

void MetaDataModel::write(QJsonObject &json) const
{
	json["participant name"] = m_participant;
	json["instructor name"] = m_instructor;
	json["date of birth"] = m_dateOfBirth.toString(Qt::TextDate);
	json["date of test"] = m_dateOfTest.toString(Qt::TextDate);
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
		m_dateOfBirth.fromString(dateOfBirth.toString());
	}

	const auto &dateOfTest = json["date of test"];
	if (dateOfTest.isString())
	{
		m_dateOfTest.fromString(dateOfTest.toString());
	}

	const auto &remarks = json["remarks"];
	if (remarks.isString())
	{
		m_remarks = remarks.toString();
	}
}
