#include "testdata.h"

void TestData::Meta::write(QJsonObject &json)
{
	json["participant name"] = m_participant;
	json["instructor name"] = m_instructor;
	json["date of birth"] = m_dateOfBirth.toString(Qt::TextDate);
	json["date of test"] = m_dateOfTest.toString(Qt::TextDate);
	json["remarks"] = m_remarks;
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

