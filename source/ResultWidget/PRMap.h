#pragma once

#include "../Age.h"
#include <vector>

class PRMap
{
protected:
	std::vector<Age> m_ages;
	std::vector<std::vector<unsigned int>> m_PRs;

public:
	unsigned int lookup(const Age &age, const unsigned int &points);
};
