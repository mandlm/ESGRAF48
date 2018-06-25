#pragma once

#include "PRMap.h"

class SvkPR : public PRMap
{
public:
	SvkPR()
	{
		// clang-format off
		m_ages = {
			{ 4, 0 },
			{ 5, 0 },
			{ 6, 0 },
			{ 9, 0 }
		};

		m_PRs = {
			{ 1, 0, 0 },
			{ 1, 0, 0 },
			{ 1, 0, 0 },
			{ 1, 0, 0 },
			{ 1, 0, 0 },
			{ 1, 0, 0 },
			{ 1, 0, 0 },
			{ 1, 0, 0 },
			{ 2, 0, 0 },
			{ 2, 0, 0 },
			{ 2, 0, 0 },
			{ 2, 0, 0 },
			{ 2, 0, 0 },
			{ 2, 0, 0 },
			{ 2, 0, 0 },
			{ 2, 0, 0 },
			{ 2, 0, 0 },
			{ 2, 0, 0 },
			{ 2, 0, 0 },
			{ 2, 1, 0 },
			{ 3, 1, 0 },
			{ 4, 1, 1 },
			{ 4, 1, 1 },
			{ 7, 2, 1 },
			{ 8, 3, 3 },
			{ 8, 5, 3 },
			{ 9, 5, 3 },
			{ 12, 6, 4 },
			{ 17, 6, 4 },
			{ 18, 7, 5 },
			{ 21, 7, 6 },
			{ 21, 8, 7 },
			{ 24, 10, 7 },
			{ 28, 11, 7 },
			{ 32, 12, 9 },
			{ 34, 14, 9 },
			{ 37, 19, 11 },
			{ 42, 25, 13 },
			{ 51, 28, 16 },
			{ 53, 31, 19 },
			{ 59, 38, 25 },
			{ 71, 50, 36 },
			{ 100, 100, 100 }
		};
		// clang-format on
	}
};
