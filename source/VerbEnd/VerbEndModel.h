#pragma once

#include "CheckableItem.h"
#include "CheckableItems.h"

#include <QAbstractTableModel>

class VerbEndModel : public QAbstractTableModel
{
	Q_OBJECT

private:
	CheckableItems m_telefonat = { "Kausal (1)", "Kausal (2)", "Relativ",
		"Kausal (3)", "Final", "Temporal (1)", "Temporal (2)" };
	CheckableItems m_zaubertrick = { "Relativ", "Final (1)", "Kausal (1)",
		"Final (2)", "Temporal (1)", "Kausal (2)", "Temporal (2)" };
	CheckableItems m_zauberregel = { "Temporal (1)", "Kausal", "Final",
		"Relativ (1)", "Temporal (2)", "Relativ (2)" };

public:
	VerbEndModel(QObject *parent);
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
