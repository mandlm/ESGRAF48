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
        for (unsigned int month = 0; month < 12; ++month)
        {
            Age age(year, month);

            REQUIRE(age.years() == year);
            REQUIRE(age.months() == month);
        }
    }
}

TEST_CASE("age by reference")
{
    QDate birth(1970, 1, 1);
    QDate reference(1980, 1, 1);

    Age age(birth, reference);

    REQUIRE(age.years() == 10);
    REQUIRE(age.months() == 0);
}
