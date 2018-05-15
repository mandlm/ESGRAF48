#pragma once

#include <QJsonObject>
#include <QString>
#include <QDate>

class TestData
{
private:
	class SubTest1
	{
	public:
		void write(QJsonObject &json);
	};

private:
	SubTest1 m_subTest1Data;

public:
	void write(QJsonObject &json);
};
