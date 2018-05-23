#pragma once

#include "CheckableItem.h"

#include <QJsonObject>
#include <map>

class CheckableItems : public std::map<size_t, CheckableItem>
{
public:
    using std::map<size_t, CheckableItem>::map;

    void write(QJsonObject &json) const;
};
