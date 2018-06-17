#include "ResultModel.h"

#include "PluralPR.h"
#include "GenusPR.h"
#include "VerbEndPR.h"
#include "AkkusativPR.h"
#include "DativPR.h"

#include <QDebug>

ResultModel::ResultModel(QObject *parent)
	: QAbstractTableModel(parent)
{
	m_results = { { "V2", "SVK", "VE", "Passiv", "Genus", "Akkusativ", "Dativ",
		"Genitiv", "Plural" } };
}

int ResultModel::rowCount(const QModelIndex &parent) const
{
	return 4;
}

int ResultModel::columnCount(const QModelIndex &parent) const
{
	return 9;
}

QVariant ResultModel::data(const QModelIndex &index, int role) const
{
	if (role == Qt::DisplayRole && index.column() < m_results.size())
	{
		switch (index.row())
		{
			case 0:
			{
				auto points = m_results[index.column()].points();
				if (points != 0)
				{
					return static_cast<uint>(points);
				}
				break;
			}
			case 1:
			{
				auto pr = m_results[index.column()].pr();
				if (pr >= 84)
				{
					return static_cast<uint>(pr);
				}
				break;
			}
			case 2:
			{
				auto pr = m_results[index.column()].pr();
				if (pr < 84 && pr > 16)
				{
					return static_cast<uint>(pr);
				}
				break;
			}
			case 3:
			{
				auto pr = m_results[index.column()].pr();
				if (pr <= 16)
				{
					return static_cast<uint>(pr);
				}
				break;
			}
			default:
				break;
		};

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
				default:
					return {};
			}
		default:
			return {};
	}
}

void ResultModel::setAge(const Age &age)
{
	m_age = age;
	emit dataChanged(index(1, 0), index(4, 8));
}

void ResultModel::setPluralResult(unsigned int points)
{
	if (m_results[8].points() != points)
	{
		m_results[8].setPoints(points);
		m_results[8].setPR(PluralPR().lookup(m_age, points));
		emit dataChanged(index(0, 8), index(4, 8));
	}
}

void ResultModel::setGenusResult(unsigned int points)
{
	if (m_results[4].points() != points)
	{
		m_results[4].setPoints(points);
		m_results[4].setPR(GenusPR().lookup(m_age, points));
		emit dataChanged(index(0, 4), index(4, 4));
	}
}

void ResultModel::setVerbEndResult(unsigned int points)
{
	if (m_results[2].points() != points)
	{
		m_results[2].setPoints(points);
		m_results[2].setPR(VerbEndPR().lookup(m_age, points));
		emit dataChanged(index(0, 2), index(4, 2));
	}
}

void ResultModel::setAkkusativResult(unsigned int points)
{
	if (m_results[5].points() != points)
	{
		m_results[5].setPoints(points);
		m_results[5].setPR(AkkusativPR().lookup(m_age, points));
		emit dataChanged(index(0, 5), index(4, 5));
	}
}

void ResultModel::setDativResult(unsigned int points)
{
	if (m_results[6].points() != points)
	{
		m_results[6].setPoints(points);
		m_results[6].setPR(DativPR().lookup(m_age, points));
		emit dataChanged(index(0, 6), index(4, 6));
	}
}
