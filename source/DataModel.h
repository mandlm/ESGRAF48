#pragma once

#include "MetaDataModel.h"

#include <QJsonObject>

class DataModel : public QObject
{
	Q_OBJECT

public:
	MetaDataModel m_metaData;

public:
	DataModel(QObject *parent);

	void write(QJsonObject &target) const;
	void read(const QJsonObject &source);
};
