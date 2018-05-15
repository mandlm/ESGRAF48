#pragma once

#include <QJsonObject>
#include <QString>
#include <QDate>

class TestData
{
private:
	class Meta
	{
	private:
		QString m_participant;
		QString m_instructor;
		QDate m_dateOfBirth;
		QDate m_dateOfTest;
		QString m_remarks;

	public:
		void write(QJsonObject &json);
	};

	class SubTest1
	{
	public:
		void write(QJsonObject &json);
	};

private:
	Meta m_metaData;
	SubTest1 m_subTest1Data;

public:
	void write(QJsonObject &json);
};
