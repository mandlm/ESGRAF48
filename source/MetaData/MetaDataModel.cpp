#include "MetaDataModel.h"

#include <QTextTable>
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

void MetaDataModel::printTo(QTextCursor &cursor) const
{
	cursor.insertBlock();

	QTextTableFormat tableFormat;
	tableFormat.setBorderStyle(QTextTableFormat::BorderStyle_None);
	tableFormat.setCellPadding(2);
	tableFormat.setCellSpacing(0);

	tableFormat.setColumnWidthConstraints({QTextLength(QTextLength::PercentageLength, 25),
	                                       QTextLength(QTextLength::PercentageLength, 25),
	                                       QTextLength(QTextLength::PercentageLength, 25),
	                                       QTextLength(QTextLength::PercentageLength, 25)});

	QTextTable *table = cursor.insertTable(4, 4, tableFormat);
	table->mergeCells(1, 2, 1, 2);
	table->mergeCells(2, 2, 2, 2);

	cursor.insertText("Name, Vorname");
	cursor.movePosition(QTextCursor::NextCell);
	cursor.insertText(m_participant);
	cursor.movePosition(QTextCursor::NextCell);
	cursor.insertText("Untersucher(in)");
	cursor.movePosition(QTextCursor::NextCell);
	cursor.insertText(m_instructor);
	cursor.movePosition(QTextCursor::NextRow);

	cursor.insertText("Geburtsdatum");
	cursor.movePosition(QTextCursor::NextCell);
	cursor.insertText(m_dateOfBirth.toString("dd.MM.yyyy"));
	cursor.movePosition(QTextCursor::NextCell);
	if (!m_remarks.trimmed().isEmpty())
	{
		cursor.insertText("Bemerkungen:");
	}
	cursor.movePosition(QTextCursor::NextRow);
	
	cursor.insertText("Untersuchungsdatum");
	cursor.movePosition(QTextCursor::NextCell);
	cursor.insertText(m_dateOfTest.toString("dd.MM.yyyy"));
	cursor.movePosition(QTextCursor::NextCell);
	cursor.insertText(m_remarks.trimmed());
	cursor.movePosition(QTextCursor::NextRow);

	cursor.insertText("Alter am Testtag");
	cursor.movePosition(QTextCursor::NextCell);
	cursor.insertText(getAge().toString().c_str());

	cursor.movePosition(QTextCursor::End);
}

