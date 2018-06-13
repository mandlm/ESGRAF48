#include "ResultModel.h"

#include <QDebug>

ResultModel::ResultModel(QObject *parent)
	: QAbstractTableModel(parent)
{
	m_results = { { "V2", "SVK", "VE", "Passiv", "Genus", "Akkusativ", "Dativ",
		"Genitiv", "Plural" } };
}

int ResultModel::rowCount(const QModelIndex &parent) const
{
	return 5;
}

int ResultModel::columnCount(const QModelIndex &parent) const
{
	return 9;
}

QVariant ResultModel::data(const QModelIndex &index, int role) const
{
	if (role == Qt::DisplayRole)
	{
		switch (index.row())
		{
			case 0:
				if (index.column() < m_results.size())
				{
					size_t points = m_results[index.column()].points();
					if (points != 0)
					{
						return static_cast<uint>(points);
					}
				}
				break;
			case 1:
				switch (index.column())
				{
					case 8:
						{
							auto pR = getPluralPR();
							if (pR >= 84)
							{
								return pR;
							}
						}
						break;
					default:
						break;
				}
				break;
			case 2:
				switch (index.column())
				{
					case 8:
						{
							auto pR = getPluralPR();
							if (pR < 84 && pR > 16)
							{
								return pR;
							}
						}
						break;
					default:
						break;
				}
				break;
			case 3:
				switch (index.column())
				{
					case 8:
						{
							auto pR = getPluralPR();
							if (pR <= 16)
							{
								return pR;
							}
						}
						break;
					default:
						break;
				}
				break;
			default:
				break;
		}

		return "-";
	}

	return {};
}

QVariant ResultModel::headerData(
	int section, Qt::Orientation orientation, int role) const
{
	if (role != Qt::DisplayRole)
	{
		return {};
	}

	switch (orientation)
	{
		case Qt::Horizontal:
			if (m_results.size() > section)
			{
				return m_results[section].name();
			}
		case Qt::Vertical:
			switch (section)
			{
				case 0:
					return "RP";
				case 1:
					return ">= PR 84";
				case 2:
					return "< PR 84";
				case 3:
					return "<= PR 16";
				case 4:
					return "T-Wert";
				default:
					return {};
			}
		default:
			return {};
	}
}

void ResultModel::setAge(const Age &age)
{
	qDebug() << "Age:" << age.years() << "years" << age.months() << "months";
	m_age = age;
	emit dataChanged(index(1, 0), index(4, 8));
}

void ResultModel::setPluralResult(size_t points)
{
	if (m_results[8].points() != points)
	{
		m_results[8] = points;
		emit dataChanged(index(0, 8), index(4, 8));
	}
}

unsigned int ResultModel::getPluralPoints() const
{
	return m_results[8].points();
}

unsigned int ResultModel::getPluralPR() const
{
	return PluralPR().lookup(m_age, getPluralPoints());
}
