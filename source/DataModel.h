#pragma once

#include "MetaData/MetaDataModel.h"
#include "Genus/GenusModel.h"

#include <QJsonObject>

class DataModel : public QObject
{
	Q_OBJECT

public:
	MetaDataModel m_metaData;
	GenusModel m_genus;

public:
	DataModel(QObject *parent);

	void write(QJsonObject &target) const;
	void read(const QJsonObject &source);
};
