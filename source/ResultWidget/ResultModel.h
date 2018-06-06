#pragma once

#include <vector>
#include <QAbstractTableModel>

class TestResult
{
private:
	QString m_name;

public:
	TestResult(const char *name)
		: m_name(name)
	{
	}

	const QString &name() const
	{
		return m_name;
	}
};

class ResultModel : public QAbstractTableModel
{
	Q_OBJECT

private:
	std::vector<TestResult> m_results;

public:
	ResultModel(QObject *parent);

	int rowCount(const QModelIndex &parent = QModelIndex()) const override;
	int columnCount(const QModelIndex &parent = QModelIndex()) const override;

	QVariant data(
		const QModelIndex &index, int role = Qt::DisplayRole) const override;

	QVariant headerData(int section, Qt::Orientation orientation,
		int role = Qt::DisplayRole) const override;
};
