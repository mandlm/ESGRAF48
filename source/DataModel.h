#pragma once

#include "PrintableModel.h"

#include "MetaData/MetaDataModel.h"
#include "GenusModel.h"
#include "VerbEndModel.h"
#include "PluralModel.h"
#include "AkkusativModel.h"
#include "DativModel.h"

#include "WFModel.h"
#include "OTModel.h"
#include "TPrModel.h"
#include "TPeModel.h"

#include "PassivModel.h"
#include "GenitivModel.h"

#include "ResultModel.h"

#include <QPrinter>

class DataModel : public QObject
{
    Q_OBJECT

public:
    MetaDataModel m_metaData;
    VerbEndModel m_verbEnd;
    GenusModel m_genus;
    PluralModel m_plural;
    AkkusativModel m_akkusativ;
    DativModel m_dativ;

    WFModel m_wfModel;
    OTModel m_otModel;
    TPrModel m_tPrModel;
    TPeModel m_tPeModel;

    PassivModel m_passiv;
    GenitivModel m_genitiv;

    ResultModel m_results;

public:
    DataModel(QObject* parent);

    void write(const QString& filename) const;
    void read(const QString& filename);

    void printTo(QPrinter& printer) const;

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
