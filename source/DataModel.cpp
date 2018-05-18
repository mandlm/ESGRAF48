#include "DataModel.h"

DataModel::DataModel(QObject *parent)
	: QObject(parent)
	, m_metaData(this)
{
}

void DataModel::write(QJsonObject &target) const
{
	QJsonObject metaData;
	m_metaData.write(metaData);
	target["MetaData"] = metaData;
}

void DataModel::read(const QJsonObject &source)
{
	const auto &metaData = source["MetaData"];
	if (metaData.isObject())
	{
		m_metaData.read(metaData.toObject());
	}
}
