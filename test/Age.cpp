#include <catch2/catch.hpp>

#include "Age.h"

TEST_CASE("default initialization")
{
	Age age;
	REQUIRE(age.years() == 0);
	REQUIRE(age.months() == 0);
	REQUIRE(age.toString() == "0;0");

	Age age2;
	REQUIRE(!(age < age));
	REQUIRE(!(age < age2));
}

TEST_CASE("year/month initialization")
{
	for (unsigned int year = 0; year <= 100; ++year)
	{
		for (unsigned int month = 1; month <= 12; ++month)
		{
			Age age(year, month);

			REQUIRE(age.years() == year);
			REQUIRE(age.months() == month);
		}
	}
}
