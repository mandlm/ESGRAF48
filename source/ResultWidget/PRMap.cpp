#include "PRMap.h"

unsigned int PRMap::lookup(const Age &age, const unsigned int &points)
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

        return 0;
	}();

	if (ageIndex >= m_PRs.at(points).size())
	{
		return 0;
	}

	return m_PRs.at(points).at(ageIndex);
}
