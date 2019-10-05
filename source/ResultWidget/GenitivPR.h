#pragma once

#include "PRMap.h"

class GenitivPR : public PRMap
{
public:
    GenitivPR()
    {
        // clang-format off
		m_ages = {
                        { 7, 0 },
                        { 7, 6 },
                        { 8, 0 },
                        { 9, 0 }
		};

		m_PRs = {
                        { 0, 0, 0 },
                        { 1, 3, 0 },
                        { 2, 3, 0 },
                        { 2, 5, 1 },
                        { 7, 5, 1 },
                        { 8, 6, 1 },
                        { 14, 8, 2 },
                        { 18, 9, 4 },
                        { 21, 17, 7 },
                        { 29, 18, 8 },
                        { 38, 29, 14 },
                        { 50, 42, 23 },
                        { 66, 54, 33 },
                        { 82, 68, 51 },
                        { 90, 83, 72 },
                        { 96, 92, 87 },
                        { 100, 100, 100 }
		};
        // clang-format on
    }
};
