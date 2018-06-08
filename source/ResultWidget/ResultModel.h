#pragma once

#include <vector>
#include <QAbstractTableModel>
#include <QDate>

class TestResult
{
private:
	QString m_name;
	size_t m_points;

public:
	TestResult(const char *name)
		: m_name(name)
		, m_points(0)
	{
	}

	void operator=(const size_t &points)
	{
		m_points = points;
	}

	const QString &name() const
	{
		return m_name;
	}

	const size_t points() const
	{
		return m_points;
	}
};

class ResultModel : public QAbstractTableModel
{
	Q_OBJECT

private:
	QDate m_age;
	std::vector<TestResult> m_results;

public:
	ResultModel(QObject *parent);

	int rowCount(const QModelIndex &parent = QModelIndex()) const override;
	int columnCount(const QModelIndex &parent = QModelIndex()) const override;

	QVariant data(
		const QModelIndex &index, int role = Qt::DisplayRole) const override;

	QVariant headerData(int section, Qt::Orientation orientation,
		int role = Qt::DisplayRole) const override;

	void setAge(const QDate &age);
	void setPluralResult(size_t points);
};
