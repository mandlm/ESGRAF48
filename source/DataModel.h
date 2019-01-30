#pragma once

#include "MetaData/MetaDataModel.h"
#include "GenusModel.h"
#include "VerbEndModel.h"
#include "PluralModel.h"
#include "AkkusativModel.h"
#include "DativModel.h"
#include "V2SvkModel.h"
#include "TPeModel.h"
#include "PassivModel.h"
#include "GenitivModel.h"

#include "ResultModel.h"

#include <QJsonObject>

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

	V2SvkModel m_v2Svk;
	TPeModel m_tPeModel;

    PassivModel m_passiv;
    GenitivModel m_genitiv;

	ResultModel m_results;

public:
	DataModel(QObject *parent);

	std::string toHtml() const;

	void write(const QString &filename) const;
	void read(const QString &filename);

signals:
	void modelChanged();

private:
	template <class ModelType>
	void write(
		const ModelType &model, QJsonObject &target, const char *name) const
	{
		QJsonObject jsonObject;
		model.write(jsonObject);
		target[name] = jsonObject;
	}

	template <class ModelType>
	void read(
		ModelType &model, const QJsonObject &source, const char *name) const
	{
		const auto &jsonObject = source[name];
		if (jsonObject.isObject())
		{
			model.read(jsonObject.toObject());
		}
	}

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
