#include "TestResult.h"

TestResult::TestResult(const char *name)
    : m_name(name)
{
}

void TestResult::setPoints(const size_t &points)
{
	m_points = points;
}

void TestResult::setPR(const unsigned int &pr)
{
	m_pr = pr;
}

QString TestResult::name() const
{
	return m_name;
}

size_t TestResult::points() const
{
	return m_points;
}

size_t TestResult::pr() const
{
	return m_pr;
}
