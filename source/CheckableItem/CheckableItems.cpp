#include "CheckableItems.h"

#include <QJsonArray>

#include <numeric>

CheckableItems::CheckableItems(std::initializer_list<std::string> itemNames)
{
    for (const auto& itemName : itemNames)
    {
        emplace_back(itemName);
    }
}

unsigned int CheckableItems::getPoints() const
{
    return std::accumulate(begin(), end(), 0, [](int base, const CheckableItem& item) {
        return base + item.points();
    });
}
