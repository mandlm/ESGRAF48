#pragma once

#include <string>

class CheckableItem
{
private:
    bool m_checked = false;
    std::string m_text;

public:
    CheckableItem(const std::string &text);

    std::string getText() const;
    bool isChecked() const;
    void setState(bool checked);
};
