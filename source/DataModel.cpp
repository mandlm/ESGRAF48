#include "DataModel.h"

DataModel::DataModel(QObject *parent)
	: QObject(parent)
	, m_metaData(this)
	, m_verbEnd(this)
	, m_genus(this)
{
}

void DataModel::write(QJsonObject &target) const
{
	write(m_metaData, target, "MetaData");
	write(m_verbEnd, target, "VerbEnd");
	write(m_genus, target, "Genus");
}

void DataModel::read(const QJsonObject &source)
{
	read(m_metaData, source, "MetaData");
	read(m_verbEnd, source, "VerbEnd");
	read(m_genus, source, "Genus");
}
