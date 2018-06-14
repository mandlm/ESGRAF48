#pragma once

#include "../Age.h"
#include "PRMap.h"
#include <QAbstractTableModel>

class PluralPR : public PRMap
{
public:
	PluralPR()
	{
		// clang-format off
		m_ages = {
			{ 4, 0 },
			{ 4, 6 },
			{ 5, 6 },
			{ 9, 0 }
		};

		m_PRs = {
			{ 0, 0, 0 },
			{ 0, 1, 0 },
			{ 0, 1, 0 },
			{ 1, 1, 0 },
			{ 7, 2, 1 },
			{ 10, 4, 1},
			{ 26, 10, 2 },
			{ 57, 25, 7 },
			{ 79, 56, 27 },
			{ 100, 100, 100 }
		};
		// clang-format on
	}
};

class TestResult
{
private:
	QString m_name;
	size_t m_points = 0;
	size_t m_pr = 0;

public:
	TestResult(const char *name)
		: m_name(name)
	{
	}

	void setPoints(const size_t &points)
	{
		m_points = points;
	}

	void setPR(const unsigned int &pr)
	{
		m_pr = pr;
	}

	const QString &name() const
	{
		return m_name;
	}

	const size_t points() const
	{
		return m_points;
	}
	
	const size_t pr() const
	{
		return m_pr;
	}
};

class ResultModel : public QAbstractTableModel
{
	Q_OBJECT

private:
	Age m_age;
	std::vector<TestResult> m_results;

public:
	ResultModel(QObject *parent);

	int rowCount(const QModelIndex &parent = QModelIndex()) const override;
	int columnCount(const QModelIndex &parent = QModelIndex()) const override;

	QVariant data(
		const QModelIndex &index, int role = Qt::DisplayRole) const override;

	QVariant headerData(int section, Qt::Orientation orientation,
		int role = Qt::DisplayRole) const override;

	void setAge(const Age &age);
	void setPluralResult(size_t points);
};
