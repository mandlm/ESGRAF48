#pragma once

#include "CheckableItems.h"

#include <QString>

class CheckableTest
{
private:
	CheckableItems m_items;
	QString m_name;

public:
	CheckableTest(const char *name, std::initializer_list<std::string> items);

	size_t size() const;
	const QString &name() const;
	const CheckableItems &items() const;
	CheckableItems &items();
};

using CheckableTests = std::vector<CheckableTest>;

