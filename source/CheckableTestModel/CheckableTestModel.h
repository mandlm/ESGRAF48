#pragma once

#include "../PrintableModel.h"
#include "CheckableTest.h"

#include <QAbstractTableModel>
#include <QTextCursor>

class CheckableTestModel : public QAbstractTableModel, protected PrintableModel
{
	Q_OBJECT

protected:
	CheckableTests m_tests;

public:
	CheckableTestModel(QObject *parent);

	int rowCount(const QModelIndex &parent = QModelIndex()) const override;
	int columnCount(const QModelIndex &parent = QModelIndex()) const override;

	QVariant data(
		const QModelIndex &index, int role = Qt::DisplayRole) const override;
	Qt::ItemFlags flags(const QModelIndex &index) const override;
	bool setData(const QModelIndex &index, const QVariant &value,
		int role = Qt::EditRole) override;

	QVariant headerData(int section, Qt::Orientation orientation,
		int role = Qt::DisplayRole) const override;

	unsigned int getPoints() const;

	void printTo(QTextCursor &cursor) const override;

protected:
	virtual bool isValidIndex(const QModelIndex &index) const;

	virtual std::string getName() const = 0;

	virtual void printTableTo(QTextCursor &cursor) const;
	virtual void printSummaryTo(QTextCursor &cursor) const;

	static void setCellText(QTextTable &table, int row, int column, const QString &text);
	static void setCellChecked(QTextTable &table, int row, int column, bool check);

	template <typename NumberType>
	static void setCellNumber(QTextTable &table, int row, int column, const NumberType &number)
	{
		setCellText(table, row, column, QString::number(number));
	}

private:
	CheckableItems &getItems(const QModelIndex &index);
	const CheckableItems &getItems(const QModelIndex &index) const;

	CheckableItem &getItem(const QModelIndex &index);
	const CheckableItem &getItem(const QModelIndex &index) const;
};

