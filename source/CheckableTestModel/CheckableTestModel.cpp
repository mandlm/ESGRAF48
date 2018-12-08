#include "CheckableTestModel.h"

#include <QJsonArray>
#include <QSize>
#include <QTextTable>
#include <QDebug>

CheckableTestModel::CheckableTestModel(QObject *parent)
    : QAbstractTableModel(parent)
{
}

int CheckableTestModel::rowCount(const QModelIndex &) const
{
	return static_cast<int>(m_tests.size());
}

int CheckableTestModel::columnCount(const QModelIndex &) const
{
	int columnCount = 0;

	for (const auto &test : m_tests)
	{
		columnCount = std::max(columnCount, static_cast<int>(test.size()));
	}

	return columnCount;
}

QVariant CheckableTestModel::data(const QModelIndex &index, int role) const
{
	if (!isValidIndex(index))
	{
		return {};
	}

	try
	{
		auto &item = getItem(index);

		switch (role)
		{
			case Qt::DisplayRole:
			{
				return item.getText().c_str();
			}
			case Qt::CheckStateRole:
			{
				return item.isChecked() ? Qt::Checked : Qt::Unchecked;
			}
		}
	}
	catch (std::runtime_error &e)
	{
		qDebug() << "CheckableTestModel::data" << index << e.what();
	}

	return {};
}

Qt::ItemFlags CheckableTestModel::flags(const QModelIndex &index) const
{
	if (isValidIndex(index))
	{
		return Qt::ItemIsEnabled | Qt::ItemIsUserCheckable;
	}

	return Qt::NoItemFlags;
}

bool CheckableTestModel::setData(const QModelIndex &index, const QVariant &value, int role)
{
	if (!isValidIndex(index))
	{
		return false;
	}

	try
	{
		if (role == Qt::CheckStateRole)
		{
			auto &item = getItem(index);
			item.setState(value.toBool());
			emit dataChanged(index, index);
			return true;
		}
	}
	catch (std::runtime_error &e)
	{
		qDebug() << "CheckableTestModel::setData" << index << e.what();
	}

	return false;
}

QVariant CheckableTestModel::headerData(int section, Qt::Orientation orientation, int role) const
{
	if (role == Qt::DisplayRole && orientation == Qt::Vertical)
	{
		if (section < m_tests.size())
		{
			return m_tests.at(section).name();
		}
	}

	return QAbstractTableModel::headerData(section, orientation, role);
}

bool CheckableTestModel::isValidIndex(const QModelIndex &index) const
{
	if (index.row() < m_tests.size())
	{
		return index.column() < m_tests.at(index.row()).size();
	}

	return false;
}

void CheckableTestModel::printTo(QTextCursor &cursor) const
{
	QTextCharFormat headerFormat;
	headerFormat.setFontPointSize(10);
	cursor.insertBlock();
	cursor.insertText("\n");
	cursor.insertText(getName().c_str(), headerFormat);

	printTableTo(cursor);
	cursor.movePosition(QTextCursor::End);
	cursor.insertBlock();
	cursor.insertText("\n");
	printSummaryTo(cursor);
	cursor.movePosition(QTextCursor::End);
}

void CheckableTestModel::printTableTo(QTextCursor &cursor) const
{
	QTextTableFormat tableFormat;
	tableFormat.setCellPadding(2);
	tableFormat.setCellSpacing(0);

	tableFormat.setColumnWidthConstraints({QTextLength(QTextLength::PercentageLength, 20),
	                                       QTextLength(QTextLength::PercentageLength, 9),
	                                       QTextLength(QTextLength::PercentageLength, 9),
	                                       QTextLength(QTextLength::PercentageLength, 9),
	                                       QTextLength(QTextLength::PercentageLength, 9),
	                                       QTextLength(QTextLength::PercentageLength, 9),
	                                       QTextLength(QTextLength::PercentageLength, 9),
	                                       QTextLength(QTextLength::PercentageLength, 9),
	                                       QTextLength(QTextLength::PercentageLength, 9),
	                                       QTextLength(QTextLength::PercentageLength, 1),
	                                       QTextLength(QTextLength::PercentageLength, 3),
	                                       QTextLength(QTextLength::PercentageLength, 1),
	                                       QTextLength(QTextLength::PercentageLength, 3)});

	QTextTable *table = cursor.insertTable(m_tests.size() * 2, 13, tableFormat);

	const char *emptyBox = "\u2610";
	//const char *checkBox = "\u2611";
	const char *checkBox = "x";

	auto insertText = [&table](int row, int column, const QString &text) {
		auto cell = table->cellAt(row, column);
		auto textCursor = cell.firstCursorPosition();

		auto blockFormat = textCursor.blockFormat();
		blockFormat.setAlignment(Qt::AlignCenter);
		textCursor.setBlockFormat(blockFormat);

		auto cellFormat = cell.format();
		cellFormat.setVerticalAlignment(QTextCharFormat::AlignMiddle);
		cell.setFormat(cellFormat);

		auto charFormat = textCursor.charFormat();
		charFormat.setVerticalAlignment(QTextCharFormat::AlignMiddle);
		charFormat.setFontPointSize(8);
		textCursor.setCharFormat(charFormat);
		
		textCursor.insertText(text);
	};

	int currentRow = 0;
	for (const auto &test : m_tests)
	{
		table->mergeCells(currentRow, 0, 2, 1);

		int currentColumn = 0;

		insertText(currentRow, currentColumn, test.name());
		currentColumn++;

		for (const auto &item : test.items())
		{
			insertText(currentRow, currentColumn, item.getText().c_str());
			insertText(currentRow + 1, currentColumn, item.isChecked() ? checkBox : emptyBox);

			currentColumn++;
		}

		insertText(currentRow + 1, 12, QString::number(test.getPoints()));

		currentRow += 2;
	}
}
	
void CheckableTestModel::printSummaryTo(QTextCursor &cursor) const
{
	QTextTableFormat tableFormat;
	tableFormat.setCellPadding(2);
	tableFormat.setCellSpacing(0);

	tableFormat.setColumnWidthConstraints({QTextLength(QTextLength::PercentageLength, 76),
	                                       QTextLength(QTextLength::PercentageLength, 20),
	                                       QTextLength(QTextLength::PercentageLength, 1),
	                                       QTextLength(QTextLength::PercentageLength, 3)});

	QTextTable *table = cursor.insertTable(1, 4, tableFormat);

	auto insertText = [&table](int row, int column, const QString &text) {
		auto cell = table->cellAt(row, column);
		auto textCursor = cell.firstCursorPosition();

		auto blockFormat = textCursor.blockFormat();
		blockFormat.setAlignment(Qt::AlignCenter);
		textCursor.setBlockFormat(blockFormat);

		auto cellFormat = cell.format();
		cellFormat.setVerticalAlignment(QTextCharFormat::AlignMiddle);
		cell.setFormat(cellFormat);

		auto charFormat = textCursor.charFormat();
		charFormat.setVerticalAlignment(QTextCharFormat::AlignMiddle);
		charFormat.setFontPointSize(8);
		textCursor.setCharFormat(charFormat);
		
		textCursor.insertText(text);
	};

	insertText(0, 1, "Rohwertpunkte Total:");
	insertText(0, 3, QString::number(getPoints()));
}

CheckableItems &CheckableTestModel::getItems(const QModelIndex &index)
{
	if (index.row() < m_tests.size())
	{
		return m_tests.at(index.row()).items();
	}

	throw std::runtime_error("invalid index");
}

const CheckableItems &CheckableTestModel::getItems(const QModelIndex &index) const
{
	if (index.row() < m_tests.size())
	{
		return m_tests.at(index.row()).items();
	}

	throw std::runtime_error("invalid index");
}

CheckableItem &CheckableTestModel::getItem(const QModelIndex &index)
{
	auto &items = getItems(index);
	if (index.column() < items.size())
	{
		return items.at(index.column());
	}

	throw std::runtime_error("invalid index");
}

const CheckableItem &CheckableTestModel::getItem(const QModelIndex &index) const
{
	auto &items = getItems(index);
	if (index.column() < items.size())
	{
		return items.at(index.column());
	}

	throw std::runtime_error("invalid index");
}

unsigned int CheckableTestModel::getPoints() const
{
	unsigned int points = 0;

	for (const auto &test : m_tests)
	{
		points += test.getPoints();
	}

	return points;
}
