#pragma once

#include <QDate>

class Age
{
private:
    unsigned int m_years = 0;
    unsigned int m_months = 0;

public:
    Age() = default;
    Age(unsigned int years, unsigned int months);
    Age(const QDate& birth, const QDate& reference);

    bool operator<(const Age& cmp) const;

    unsigned int years() const;
    unsigned int months() const;

    std::string toString() const;
};
