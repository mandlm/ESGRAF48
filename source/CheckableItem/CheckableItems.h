#pragma once

#include "CheckableItem.h"

#include <QJsonObject>
#include <vector>

class CheckableItems : public std::vector<CheckableItem>
{
public:
    CheckableItems(std::initializer_list<std::string> itemNames);

    unsigned int getPoints() const;
};
