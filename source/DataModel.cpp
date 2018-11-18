#include "DataModel.h"
#include "DataModel.pb.h"

#include <sstream>

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
    , m_passiv(this)
    , m_genitiv(this)
{
	connect(&m_plural, &PluralModel::dataChanged, this, &DataModel::pluralModelChanged);
	connect(&m_metaData, &MetaDataModel::dataChanged, this, &DataModel::metaDataChanged);
	connect(&m_genus, &GenusModel::dataChanged, this, &DataModel::genusModelChanged);
	connect(&m_verbEnd, &VerbEndModel::dataChanged, this, &DataModel::verbEndModelChanged);
	connect(&m_akkusativ, &AkkusativModel::dataChanged, this, &DataModel::akkusativModelChanged);
	connect(&m_dativ, &DativModel::dataChanged, this, &DataModel::dativModelChanged);
	connect(&m_v2Svk, &V2SvkModel::dataChanged, this, &DataModel::v2SvkModelChanged);
	connect(&m_passiv, &PassivModel::dataChanged, this, &DataModel::passivModelChanged);
	connect(&m_genitiv, &GenitivModel::dataChanged, this, &DataModel::genitivModelChanged);
}

void DataModel::writeProtoBuf(std::ostream &outStream) const
{
	ESGRAF48::DataModel dataModel;

	m_metaData.writeProtoBuf(*dataModel.mutable_metadata());
	m_v2Svk.writeProtoBuf(*dataModel.mutable_v2svk());
	m_verbEnd.writeProtoBuf(*dataModel.mutable_verbend());
	m_genus.writeProtoBuf(*dataModel.mutable_genus());

	dataModel.SerializeToOstream(&outStream);
}

void DataModel::readProtoBuf(std::istream &inStream)
{
	ESGRAF48::DataModel dataModel;
	dataModel.ParseFromIstream(&inStream);

	m_metaData.readProtoBuf(dataModel.metadata());
	m_v2Svk.readProtoBuf(dataModel.v2svk());
	m_verbEnd.readProtoBuf(dataModel.verbend());
	m_genus.readProtoBuf(dataModel.genus());
}

std::string DataModel::toHtml() const
{
	std::stringstream out;

	out << "<html>" << std::endl;
	out << "<head>" << std::endl;
	out << "<style>" << std::endl;
	out << "body {" << std::endl;
	out << "font-family:sans-serif;" << std::endl;
	out << "}" << std::endl;
	out << "</style>" << std::endl;
	out << "</head>" << std::endl;
	out << "<body>" << std::endl;
	out << "<h2>ESGRAF 4-8 Auswertungsbogen</h2>" << std::endl;
	out << "<p>" << std::endl;
	out << m_metaData.toHtml();
	out << "</p>" << std::endl;
	out << "</body>" << std::endl;
	out << "</html>" << std::endl;

	return out.str();
}

void DataModel::pluralModelChanged()
{
	m_results.setPluralResult(m_plural.getPoints());

	emit modelChanged();
}

void DataModel::metaDataChanged()
{
	m_results.setAge(m_metaData.getAge());

	emit modelChanged();
}

void DataModel::genusModelChanged()
{
	m_results.setGenusResult(m_genus.getPoints());

	emit modelChanged();
}

void DataModel::verbEndModelChanged()
{
	m_results.setVerbEndResult(m_verbEnd.getPoints());

	emit modelChanged();
}

void DataModel::akkusativModelChanged()
{
	m_results.setAkkusativResult(m_akkusativ.getPoints());

	emit modelChanged();
}

void DataModel::dativModelChanged()
{
	m_results.setDativResult(m_dativ.getPoints());

	emit modelChanged();
}

void DataModel::v2SvkModelChanged()
{
	m_results.setV2Result(m_v2Svk.getV2Points());
	m_results.setSvkResult(m_v2Svk.getSvkPoints());

	emit modelChanged();
}

void DataModel::passivModelChanged()
{
	m_results.setPassivResult(m_passiv.getPoints());

	emit modelChanged();
}

void DataModel::genitivModelChanged()
{
	m_results.setGenitivResult(m_genitiv.getPoints());

	emit modelChanged();
}
