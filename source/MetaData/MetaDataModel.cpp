#include "MetaDataModel.h"

#include <QDebug>

#include <sstream>

MetaDataModel::MetaDataModel(QObject *parent)
    : QAbstractTableModel(parent)
{
	m_dateOfBirth = QDate::currentDate().addYears(-9);
	m_dateOfTest = QDate::currentDate();
}

int MetaDataModel::rowCount(const QModelIndex &parent) const
{
	return 1;
}

int MetaDataModel::columnCount(const QModelIndex &parent) const
{
	return 6;
}

QVariant MetaDataModel::data(const QModelIndex &modelIndex, int role) const
{
	if (role == Qt::DisplayRole || role == Qt::EditRole)
	{
		switch (modelIndex.column())
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
			case 5:
				return QString::fromStdString(getAge().toString());
			default:
				return QVariant();
		}
	}

	return QVariant();
}

Qt::ItemFlags MetaDataModel::flags(const QModelIndex &modelIndex) const
{
	return QAbstractTableModel::flags(modelIndex) | Qt::ItemIsEditable;
}

bool MetaDataModel::setData(const QModelIndex &modelIndex, const QVariant &value, int role)
{
	if (role != Qt::EditRole)
	{
		return QAbstractTableModel::setData(modelIndex, value, role);
	}

	bool valueChanged = false;

	switch (modelIndex.column())
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
				emit dataChanged(index(0, 5), index(0, 5));
				valueChanged = true;
			}
			break;
		case 3:
			if (value.toDate() != m_dateOfTest)
			{
				m_dateOfTest = value.toDate();
				emit dataChanged(index(0, 5), index(0, 5));
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

	if (valueChanged)
	{
		emit dataChanged(modelIndex, modelIndex);
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
	setData(index(0, 0), json["participant name"].toVariant(), Qt::EditRole);
	setData(index(0, 1), json["instructor name"].toVariant(), Qt::EditRole);
	setData(index(0, 2), json["date of birth"].toVariant(), Qt::EditRole);
	setData(index(0, 3), json["date of test"].toVariant(), Qt::EditRole);
	setData(index(0, 4), json["remarks"].toVariant(), Qt::EditRole);
}

//void MetaDataModel::writeProtoBuf(ESGRAF48::MetaDataModel &model) const
//{
//}

std::string MetaDataModel::toHtml() const
{
	std::ostringstream out;

	out << "<table border=\"1\" cellspacing=\"0\" cellpadding=\"2\" frame=\"box\" rules=\"all\">"
	    << std::endl;
	out << "<tr>" << std::endl;
	out << "<td width=\"25%\">Name, Vorname</td>" << std::endl;
	out << "<td width=\"25%\">" << m_participant.toHtmlEscaped().toStdString() << "</td>"
	    << std::endl;
	out << "<td width=\"25%\">Untersucher(in)</td>" << std::endl;
	out << "<td width=\"25%\">" << m_instructor.toHtmlEscaped().toStdString() << "</td>"
	    << std::endl;
	out << "</tr>" << std::endl;
	out << "<tr>" << std::endl;
	out << "<td>Geburtsdatum</td>" << std::endl;
	out << "<td>" << m_dateOfBirth.toString("dd.MM.yyyy").toHtmlEscaped().toStdString() << "</td>"
	    << std::endl;
	out << "<td colspan=\"2\">Bemerkungen</td>" << std::endl;
	out << "</tr>" << std::endl;
	out << "<tr>" << std::endl;
	out << "<td>Untersuchungsdatum</td>" << std::endl;
	out << "<td>" << m_dateOfTest.toString("dd.MM.yyyy").toHtmlEscaped().toStdString() << "</td>"
	    << std::endl;
	out << "<td colspan=\"2\" rowspan=\"2\">"
	    << m_remarks.trimmed().toHtmlEscaped().replace("\n", "<br>").toStdString() << "</td>"
	    << std::endl;
	out << "</tr>" << std::endl;
	out << "<tr>" << std::endl;
	out << "<td>Alter am Testtag</td>" << std::endl;
	out << "<td>" << getAge().toString() << "</td>" << std::endl;
	out << "</tr>" << std::endl;
	out << "</table>" << std::endl;

	return out.str();
}
