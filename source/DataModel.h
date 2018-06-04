#pragma once

#include "MetaData/MetaDataModel.h"
#include "GenusModel.h"
#include "VerbEndModel.h"
#include "PluralModel.h"

#include <QJsonObject>

class DataModel : public QObject
{
	Q_OBJECT

public:
	MetaDataModel m_metaData;
	VerbEndModel m_verbEnd;
	GenusModel m_genus;
	PluralModel m_plural;

public:
	DataModel(QObject *parent);

	void write(QJsonObject &target) const;
	void read(const QJsonObject &source);

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
};
