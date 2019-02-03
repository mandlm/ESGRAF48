#include "MetaDataModel.h"

#include <QDebug>

#include <sstream>

MetaDataModel::MetaDataModel(QObject *parent)
    : PrintableModel(parent)
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

void MetaDataModel::read(const ESGRAF48::MetaDataModel &model)
{
	setData(index(0, 0), QString::fromStdString(model.participantname()));
	setData(index(0, 1), QString::fromStdString(model.instructorname()));
	setData(index(0, 2), QString::fromStdString(model.dateofbirth()));
	setData(index(0, 3), QString::fromStdString(model.dateoftest()));
	setData(index(0, 4), QString::fromStdString(model.remarks()));
}

void MetaDataModel::write(ESGRAF48::MetaDataModel &model) const
{
	model.set_participantname(m_participant.toStdString());
	model.set_instructorname(m_instructor.toStdString());
	model.set_dateofbirth(m_dateOfBirth.toString(Qt::ISODate).toStdString());
	model.set_dateoftest(m_dateOfTest.toString(Qt::ISODate).toStdString());
	model.set_remarks(m_remarks.toStdString());
}

void MetaDataModel::printTo(QPainter &painter) const
{
	painter.setFont(tableFont());

	auto width = painter.device()->width();
	auto height = 1.5 * painter.fontMetrics().lineSpacing();

	auto hasRemarks = !m_remarks.trimmed().isEmpty();

	painter.drawText(0, 0, "Name, Vorname");
	painter.drawText(0.25 * width, 0, m_participant);
	painter.drawText(0.5 * width, 0, "Untersucher(in)");
	painter.drawText(0.75 * width, 0, m_instructor);

	painter.translate(0, height);

	painter.drawText(0, 0, "Geburtsdatum");
	painter.drawText(0.25 * width, 0, m_dateOfBirth.toString("dd.MM.yyyy"));
	if (hasRemarks)
	{
		painter.drawText(0.5 * width, 0, "Bemerkungen:");
		painter.drawText(QRect(0.5 * width, 0.5 * height, width, 2 * height), m_remarks);
	}

	painter.translate(0, height);

	painter.drawText(0, 0, "Untersuchungsdatum");
	painter.drawText(0.25 * width, 0, m_dateOfTest.toString("dd.MM.yyyy"));

	painter.translate(0, height);

	painter.drawText(0, 0, "Alter am Testtag");
	painter.drawText(0.25 * width, 0, getAge().toString().c_str());

	painter.translate(0, 2 * height);
}

Age MetaDataModel::getAge() const
{
	return {m_dateOfBirth, m_dateOfTest};
}
