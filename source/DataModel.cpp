#include "DataModel.h"
#include "DataModel.pb.h"

#include <QFile>

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
    , m_wfModel(this)
    , m_otModel(this)
    , m_tPrModel(this)
    , m_tPeModel(this)
    , m_passiv(this)
    , m_genitiv(this)
{
	connect(&m_plural, &PluralModel::dataChanged, this, &DataModel::pluralModelChanged);
	connect(&m_metaData, &MetaDataModel::dataChanged, this, &DataModel::metaDataChanged);
	connect(&m_genus, &GenusModel::dataChanged, this, &DataModel::genusModelChanged);
	connect(&m_verbEnd, &VerbEndModel::dataChanged, this, &DataModel::verbEndModelChanged);
	connect(&m_akkusativ, &AkkusativModel::dataChanged, this, &DataModel::akkusativModelChanged);
	connect(&m_dativ, &DativModel::dataChanged, this, &DataModel::dativModelChanged);

	connect(&m_wfModel, &WFModel::dataChanged, this, &DataModel::v2SvkModelChanged);
	connect(&m_otModel, &OTModel::dataChanged, this, &DataModel::v2SvkModelChanged);
	connect(&m_tPrModel, &TPrModel::dataChanged, this, &DataModel::v2SvkModelChanged);
	connect(&m_tPeModel, &TPeModel::dataChanged, this, &DataModel::v2SvkModelChanged);

	connect(&m_passiv, &PassivModel::dataChanged, this, &DataModel::passivModelChanged);
	connect(&m_genitiv, &GenitivModel::dataChanged, this, &DataModel::genitivModelChanged);
}

void DataModel::write(const QString &filename) const
{
	ESGRAF48::DataModel dataModel;

	m_metaData.write(*dataModel.mutable_metadata());

	m_wfModel.write(*dataModel.mutable_v2svk());
	m_otModel.write(*dataModel.mutable_v2svk());
	m_tPrModel.write(*dataModel.mutable_v2svk());
	m_tPeModel.write(*dataModel.mutable_v2svk());

	m_verbEnd.write(*dataModel.mutable_verbend());
	m_genus.write(*dataModel.mutable_genus());
	m_akkusativ.write(*dataModel.mutable_akkusativ());
	m_dativ.write(*dataModel.mutable_dativ());
	m_plural.write(*dataModel.mutable_plural());
	m_genitiv.write(*dataModel.mutable_lateskillsgenitiv());
	m_passiv.write(*dataModel.mutable_lateskillspassiv());

	QFile outFile(filename);
	if (!outFile.open(QIODevice::WriteOnly))
	{
		throw std::runtime_error("failed to open file");
	}

	bool success = dataModel.SerializeToFileDescriptor(outFile.handle());
	if (success == false)
	{
		throw std::runtime_error("filed to write file");
	}
}

void DataModel::read(const QString &filename)
{
	QFile inFile(filename);
	if (!inFile.open(QIODevice::ReadOnly))
	{
		throw std::runtime_error("failed to read file");
	}

	ESGRAF48::DataModel dataModel;
	bool success = dataModel.ParseFromFileDescriptor(inFile.handle());
	if (success == false)
	{
		throw std::runtime_error("invalid file format");
	}

	m_metaData.read(dataModel.metadata());

	m_wfModel.read(dataModel.v2svk());
	m_otModel.read(dataModel.v2svk());
	m_tPrModel.read(dataModel.v2svk());
	m_tPeModel.read(dataModel.v2svk());

	m_verbEnd.read(dataModel.verbend());
	m_genus.read(dataModel.genus());
	m_akkusativ.read(dataModel.akkusativ());
	m_dativ.read(dataModel.dativ());
	m_plural.read(dataModel.plural());
	m_genitiv.read(dataModel.lateskillsgenitiv());
	m_passiv.read(dataModel.lateskillspassiv());
}

void DataModel::printTo(QPrinter &printer) const
{
	QPainter painter;
	painter.begin(&printer);


	painter.setFont(PrintableModel::h1Font());
	painter.drawText(0, painter.fontMetrics().lineSpacing(), "ESGRAF 4-8 Auswertungsbogen");
	painter.translate(0, 3 * painter.fontMetrics().lineSpacing());

	m_metaData.printTo(painter);

	m_wfModel.printTo(painter);
	m_otModel.printTo(painter);
	m_tPrModel.printTo(painter);
	m_tPeModel.printTo(painter);
	V2SvkModel::printSummary(painter,
	                         m_wfModel.getV2Points() + m_otModel.getV2Points()
	                             + m_tPrModel.getV2Points() + m_tPeModel.getV2Points(),
	                         m_wfModel.getSvkPoints() + m_otModel.getSvkPoints()
	                             + m_tPrModel.getSvkPoints() + m_tPeModel.getSvkPoints());

	m_verbEnd.printTo(painter);
	m_genus.printTo(painter);

	printer.newPage();
	painter.resetTransform();

	m_plural.printTo(painter);

	painter.end();
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
	m_results.setV2Result(m_wfModel.getV2Points() + m_otModel.getV2Points()
	                      + m_tPrModel.getV2Points() + m_tPeModel.getV2Points());
	m_results.setSvkResult(m_wfModel.getSvkPoints() + m_otModel.getSvkPoints()
	                       + m_tPrModel.getSvkPoints() + m_tPeModel.getSvkPoints());

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
