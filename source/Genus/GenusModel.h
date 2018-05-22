#pragma once

#include <QAbstractTableModel>
#include <QJsonObject>

class GenusModel : public QAbstractTableModel
{
	Q_OBJECT

public:
	GenusModel(QObject *parent);
	int rowCount(const QModelIndex &parent = QModelIndex()) const override;
	int columnCount(const QModelIndex &parent = QModelIndex()) const override;
	QVariant data(
		const QModelIndex &index, int role = Qt::DisplayRole) const override;
	Qt::ItemFlags flags(const QModelIndex &index) const override;
	bool setData(const QModelIndex &index, const QVariant &value,
		int role = Qt::EditRole) override;

	QVariant headerData(int section, Qt::Orientation orientation,
		int role = Qt::DisplayRole) const;

	void write(QJsonObject &json) const;
	void read(const QJsonObject &json);
};
