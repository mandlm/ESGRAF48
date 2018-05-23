#pragma once

#include "MetaData/MetaDataModel.h"
#include "Genus/GenusModel.h"
#include "VerbEnd/VerbEndModel.h"

#include <QJsonObject>

class DataModel : public QObject
{
	Q_OBJECT

public:
	MetaDataModel m_metaData;
	VerbEndModel m_verbEnd;
	GenusModel m_genus;

public:
	DataModel(QObject *parent);

	void write(QJsonObject &target) const;
	void read(const QJsonObject &source);
};
