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


