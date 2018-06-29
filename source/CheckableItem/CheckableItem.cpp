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

unsigned int CheckableItem::value() const
{
	return m_value;
}

void CheckableItem::setValue(unsigned int value)
{
	m_value = value;
}

unsigned int CheckableItem::points() const
{
	return m_checked ? m_value : 0;
}

void CheckableItem::write(QJsonObject &json) const
{
	json["text"] = m_text.c_str();
	json["checked"] = m_checked;
}

void CheckableItem::read(const QJsonObject &json)
{
	const auto &text = json["text"];
	if (text.isString())
	{
		m_text = text.toString().toStdString();
	}

	const auto &checked = json["checked"];
	if (checked.isBool())
	{
		m_checked = checked.toBool();
	}
}
