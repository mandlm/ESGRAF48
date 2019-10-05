#pragma once

#include <QJsonObject>

#include <string>

class CheckableItem
{
private:
    bool m_checked = false;
    std::string m_text;
    unsigned int m_value = 1;

public:
    CheckableItem() = default;
    CheckableItem(const std::string& text);

    std::string getText() const;

    bool isChecked() const;
    void setState(bool checked);

    unsigned int value() const;
    void setValue(unsigned int value);

    unsigned int points() const;
};
