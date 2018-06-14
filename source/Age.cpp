#include "Age.h"

#include <QDebug>
#include <sstream>

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
	
bool Age::operator<(const Age &cmp) const
{
	if (m_years == cmp.m_years)
	{
		return m_months < cmp.m_months;
	}

	return m_years < cmp.m_years;
}
	
unsigned int Age::years() const
{
	return m_years;
}

unsigned int Age::months() const
{
	return m_months;
}
 
std::string Age::toString() const
{
	std::ostringstream result;
	result << m_years << ";" << m_months;
	return result.str();
}
