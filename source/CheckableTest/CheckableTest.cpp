#include "CheckableTest.h"

#include <numeric>

CheckableTest::CheckableTest(
	const char *name, std::initializer_list<std::string> items)
	: m_name(name)
	, m_items(items)
{
}

size_t CheckableTest::size() const
{
	return m_items.size();
}

const QString &CheckableTest::name() const
{
	return m_name;
}

const CheckableItems &CheckableTest::items() const
{
	return m_items;
}

CheckableItems &CheckableTest::items()
{
	return m_items;
}
	
unsigned int CheckableTest::getPoints() const
{
	return m_items.getPoints();
}
