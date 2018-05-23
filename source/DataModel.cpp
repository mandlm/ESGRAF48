#include "DataModel.h"

DataModel::DataModel(QObject *parent)
	: QObject(parent)
	, m_metaData(this)
	, m_genus(this)
{
}

void DataModel::write(QJsonObject &target) const
{
	QJsonObject metaData;
	m_metaData.write(metaData);
	target["MetaData"] = metaData;

	QJsonObject genus;
	m_genus.write(genus);
	target["Genus"] = genus;
}

void DataModel::read(const QJsonObject &source)
{
	const auto &metaData = source["MetaData"];
	if (metaData.isObject())
	{
		m_metaData.read(metaData.toObject());
	}

    const auto &genus = source["Genus"];
    if (genus.isObject())
    {
        m_genus.read(genus.toObject());
    }
}
