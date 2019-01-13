#pragma once

#include "PrintableModel.h"

#include "Age.h"

#include "MetaDataModel.pb.h"

#include <QAbstractTableModel>
#include <QString>
#include <QDate>

class MetaDataModel : public QAbstractTableModel, public PrintableModel
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
	Qt::ItemFlags flags(const QModelIndex &index) const override;
	bool setData(const QModelIndex &index, const QVariant &value,
		int role = Qt::EditRole) override;

	void read(const ESGRAF48::MetaDataModel &model);
	void write(ESGRAF48::MetaDataModel &model) const;

	void printTo(QPainter &painter) const override;

	Age getAge() const
	{
		return { m_dateOfBirth, m_dateOfTest };
	}
};
