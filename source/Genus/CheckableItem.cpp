#include "CheckableItem.h"

CheckableItem::CheckableItem(const std::string &text)
    : m_text(text)
{
}

std::string CheckableItem::getText() const
{
    return m_text;
}

bool CheckableItem::isChecked() const
{
    return m_checked;
}

void CheckableItem::setState(bool checked)
{
    m_checked = checked;
}
