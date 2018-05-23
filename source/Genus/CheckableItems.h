#pragma once

#include "CheckableItem.h"

#include <QJsonObject>
#include <map>

class CheckableItems : public std::vector<CheckableItem>
{
public:
    CheckableItems(std::initializer_list<std::string> itemNames);

    void write(QJsonArray &json) const;
    void read(const QJsonArray &json);
};
