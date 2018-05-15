#include "testdata.h"

void TestData::SubTest1::write(QJsonObject &json)
{
	json["type"] = "SubTest1";
}

void TestData::write(QJsonObject &json)
{
	QJsonObject subTest1Data;
	m_subTest1Data.write(subTest1Data);
	json["SubTest1"] = subTest1Data;
}

