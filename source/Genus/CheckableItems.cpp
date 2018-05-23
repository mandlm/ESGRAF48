#include "CheckableItems.h"

void CheckableItems::write(QJsonObject &json) const
{
    for (const auto &pair : *this)
    {
        json[pair.second.getText().c_str()] =
            pair.second.isChecked();
    }
}
