#pragma once

#include "PRMap.h"

class PluralPR : public PRMap
{
public:
	PluralPR()
	{
		// clang-format off
		m_ages = {
			{ 4, 0 },
			{ 4, 6 },
			{ 5, 6 },
			{ 9, 0 }
		};

		m_PRs = {
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
	}
};
