#pragma once

#include "CheckableItem.h"
#include "CheckableItems.h"

#include <QAbstractTableModel>

class GenusModel : public QAbstractTableModel
{
	Q_OBJECT

private:
	CheckableItems m_tiere = { "Tiger", "Bär", "Katze", "Pferd", "Gans",
		"Elefant", "Katze", "Hund" };
	CheckableItems m_futter = { "Salat", "Fleisch", "Knocken", "Banane",
		"Apfel", "Möhre", "Honig", "Zucker" };
	CheckableItems m_zirkus = { "Kiste", "Holz", "Vorhang", "Baum" };

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
		int role = Qt::DisplayRole) const override;

	void write(QJsonObject &json) const;
	void read(const QJsonObject &json);

private:
	bool isValidIndex(const QModelIndex &index) const;

	CheckableItems &getItems(const QModelIndex &index);
	const CheckableItems &getItems(const QModelIndex &index) const;

	CheckableItem &getItem(const QModelIndex &index);
	const CheckableItem &getItem(const QModelIndex &index) const;
};
