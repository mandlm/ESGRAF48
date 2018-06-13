#pragma once

#include "../Age.h"
#include <vector>
#include <QAbstractTableModel>

class PluralPR
{
	// clang-format off
	const std::vector<Age> m_ages = {
		{ 4, 0 },
		{ 4, 6 },
		{ 5, 6 },
		{ 9, 0 }
	};

	const std::vector<std::vector<unsigned int>> m_PRs = {
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

public:
	unsigned int lookup(const Age &age, const unsigned int &points)
	{
		if (points >= m_PRs.size())
		{
			return 0;
		}

		auto ageIndex = [&]() -> size_t {
			if (m_ages.empty())
			{
				return 0;
			}

			if (age < m_ages.front())
			{
				return 0;
			}

			if (m_ages.back() < age)
			{
				return m_ages.size() - 1;
			}

			for (size_t index = 1; index < m_ages.size(); ++index)
			{
				if (age < m_ages.at(index))
				{
					return index - 1;
				}
			}
		}();

		if (ageIndex >= m_PRs.at(points).size())
		{
			return 0;
		}

		return m_PRs.at(points).at(ageIndex);
	}
};

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

private:
	unsigned int getPluralPoints() const;
	unsigned int getPluralPR() const;
};
