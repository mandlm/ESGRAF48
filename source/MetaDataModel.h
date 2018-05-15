#pragma once

#include <QAbstractTableModel>
#include <QString>
#include <QDate>

class MetaDataModel : public QAbstractTableModel
{
	Q_OBJECT

private:
	QString m_participant;
	QString m_instructor;
	QDate m_dateOfBirth;
	QDate m_dateOfTest;
	QString m_remarks;

public:
	MetaDataModel(QObject *parent);
	int rowCount(const QModelIndex &parent = QModelIndex()) const override;
	int columnCount(const QModelIndex &parent = QModelIndex()) const override;
	QVariant data(
		const QModelIndex &index, int role = Qt::DisplayRole) const override;
};
