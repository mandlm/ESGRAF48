#include "testdata.h"

void TestData::Meta::write(QJsonObject &json)
{
	json["participant"] = m_participant;
	json["instructor"] = m_instructor;
}

void TestData::SubTest1::write(QJsonObject &json)
{
	json["type"] = "SubTest1";
}

void TestData::write(QJsonObject &json)
{
	QJsonObject metaData;
	m_metaData.write(metaData);
	json["Meta"] = metaData;

	QJsonObject subTest1Data;
	m_subTest1Data.write(subTest1Data);
	json["SubTest1"] = subTest1Data;
}

