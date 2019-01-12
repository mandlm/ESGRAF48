#pragma once

#include "PrintableModel.h"

#include "MetaData/MetaDataModel.h"
#include "GenusModel.h"
#include "VerbEndModel.h"
#include "PluralModel.h"
#include "AkkusativModel.h"
#include "DativModel.h"
#include "V2SvkModel.h"
#include "PassivModel.h"
#include "GenitivModel.h"

#include "ResultModel.h"

#include <QPainter>

class DataModel : public QObject, public PrintableModel
{
	Q_OBJECT

public:
	MetaDataModel m_metaData;
	VerbEndModel m_verbEnd;
	GenusModel m_genus;
	PluralModel m_plural;
	AkkusativModel m_akkusativ;
	DativModel m_dativ;
	V2SvkModel m_v2Svk;
    PassivModel m_passiv;
    GenitivModel m_genitiv;

	ResultModel m_results;

public:
	DataModel(QObject *parent);

	void write(std::ostream &outStream) const;
	void read(std::istream &inStream);

	void printTo(QPainter &painter) const override;

signals:
	void modelChanged();

private slots:
	void pluralModelChanged();
	void metaDataChanged();
	void genusModelChanged();
	void verbEndModelChanged();
	void akkusativModelChanged();
	void dativModelChanged();
	void v2SvkModelChanged();
    void passivModelChanged();
    void genitivModelChanged();
};
