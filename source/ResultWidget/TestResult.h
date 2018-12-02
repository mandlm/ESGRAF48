#pragma once

#include <QString>

class TestResult
{
private:
	QString m_name;
	size_t m_points = 0;
	size_t m_pr = 0;

public:
	TestResult(const char *name);

	void setPoints(const size_t &points);
	void setPR(const unsigned int &pr);

	QString name() const;
	size_t points() const;
	size_t pr() const;
};

