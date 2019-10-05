#pragma once

#include "PRMap.h"

class PassivPR : public PRMap
{
public:
    PassivPR()
    {
        // clang-format off
		m_ages = {
                        { 7, 0 },
                        { 8, 6 },
			{ 9, 0 }
		};

		m_PRs = {
                        { 1, 0 },
                        { 2, 0 },
                        { 6, 2 },
                        { 9, 3 },
                        { 23, 12 },
                        { 34, 23 },
                        { 55, 41 },
                        { 71, 59 },
                        { 85, 76 },
                        { 94, 84 },
                        { 100, 100 }
		};
        // clang-format on
    }
};
