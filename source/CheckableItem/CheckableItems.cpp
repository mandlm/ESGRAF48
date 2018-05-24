#include "CheckableItems.h"

#include <QJsonArray>

CheckableItems::CheckableItems(std::initializer_list<std::string> itemNames)
{
	for (const auto &itemName : itemNames)
	{
		emplace_back(itemName);
	}
}

void CheckableItems::write(QJsonArray &json) const
{
	for (const auto &item : *this)
	{
		QJsonObject itemObject;
		item.write(itemObject);
		json.append(itemObject);
	}
}

void CheckableItems::read(const QJsonArray &json)
{
	clear();

	for (const auto &itemObject : json)
	{
		if (itemObject.isObject())
		{
			CheckableItem item;
			item.read(itemObject.toObject());
			emplace_back(item);
		}
	}
}
