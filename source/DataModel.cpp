#include "DataModel.h"

#include <QDebug>

DataModel::DataModel(QObject *parent)
	: QObject(parent)
	, m_metaData(this)
	, m_verbEnd(this)
	, m_genus(this)
	, m_plural(this)
	, m_results(this)
	, m_akkusativ(this)
	, m_dativ(this)
	, m_v2Svk(this)
{
	connect(&m_plural, &PluralModel::dataChanged, this,
		&DataModel::pluralModelChanged);
	connect(&m_metaData, &PluralModel::dataChanged, this,
		&DataModel::metaDataChanged);
	connect(&m_genus, &GenusModel::dataChanged, this,
		&DataModel::genusModelChanged);
	connect(&m_verbEnd, &VerbEndModel::dataChanged, this,
		&DataModel::verbEndModelChanged);
	connect(&m_akkusativ, &AkkusativModel::dataChanged, this,
		&DataModel::akkusativModelChanged);
	connect(&m_dativ, &DativModel::dataChanged, this,
		&DataModel::dativModelChanged);
	connect(&m_v2Svk, &V2SvkModel::dataChanged, this,
		&DataModel::v2SvkModelChanged);
}

void DataModel::write(QJsonObject &target) const
{
	write(m_metaData, target, "MetaData");
	write(m_verbEnd, target, "VerbEnd");
	write(m_genus, target, "Genus");
	write(m_plural, target, "Plural");
	write(m_akkusativ, target, "Akkusativ");
	write(m_dativ, target, "Dativ");
	write(m_v2Svk, target, "V2Svk");
}

void DataModel::read(const QJsonObject &source)
{
	read(m_metaData, source, "MetaData");
	read(m_verbEnd, source, "VerbEnd");
	read(m_genus, source, "Genus");
	read(m_plural, source, "Plural");
	read(m_akkusativ, source, "Akkusativ");
	read(m_dativ, source, "Dativ");
	read(m_v2Svk, source, "V2Svk");
}

void DataModel::pluralModelChanged()
{
	m_results.setPluralResult(m_plural.getPoints());
}

void DataModel::metaDataChanged()
{
	m_results.setAge(m_metaData.getAge());
}

void DataModel::genusModelChanged()
{
	m_results.setGenusResult(m_genus.getPoints());
}

void DataModel::verbEndModelChanged()
{
	m_results.setVerbEndResult(m_verbEnd.getPoints());
}

void DataModel::akkusativModelChanged()
{
	m_results.setAkkusativResult(m_akkusativ.getPoints());
}

void DataModel::dativModelChanged()
{
	m_results.setDativResult(m_dativ.getPoints());
}

void DataModel::v2SvkModelChanged()
{
	m_results.setV2Result(m_v2Svk.getV2Points());
	m_results.setSvkResult(m_v2Svk.getSvkPoints());
}
