#include "Age.h"

#include <QDebug>

Age::Age(unsigned int years, unsigned int months)
	: m_years(years)
	, m_months(months)
{
}

Age::Age(const QDate &birth, const QDate &reference)
{
	if (reference < birth)
	{
		qDebug() << "test (" << reference << ") before birth (" << birth << ")";
		m_years = 0;
		m_months = 0;

		return;
	}

	int years = reference.year() - birth.year();
	int months = reference.month() - birth.month();

	if (months == 0 && reference.day() < birth.day())
	{
		months--;
	}

	if (months < 0)
	{
		years--;
		months = (months + 12) % 12;
	}

	m_years = years;
	m_months = months;
}
	
unsigned int Age::years() const
{
	return m_years;
}

unsigned int Age::months() const
{
	return m_months;
}
