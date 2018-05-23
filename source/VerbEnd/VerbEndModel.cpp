#include "VerbEndModel.h"

#include <QJsonArray>
#include <QDebug>

VerbEndModel::VerbEndModel(QObject *parent)
	: QAbstractTableModel(parent)
{
}

int VerbEndModel::rowCount(const QModelIndex &parent) const
{
	return 3;
}

int VerbEndModel::columnCount(const QModelIndex &parent) const
{
	return 7;
}

QVariant VerbEndModel::data(const QModelIndex &index, int role) const
{
	if (!isValidIndex(index))
	{
		return {};
	}

	try
	{
		auto &item = getItem(index);

		if (role == Qt::DisplayRole)
		{
			return item.getText().c_str();
		}

		if (role == Qt::CheckStateRole)
		{
			return item.isChecked() ? Qt::Checked : Qt::Unchecked;
		}
	}
	catch (std::runtime_error &e)
	{
		qDebug() << "VerbEndModel::data" << index << e.what();
	}

	return {};
}

Qt::ItemFlags VerbEndModel::flags(const QModelIndex &index) const
{
	if (isValidIndex(index))
	{
		return Qt::ItemIsEnabled | Qt::ItemIsUserCheckable;
	}

	return Qt::NoItemFlags;
}

bool VerbEndModel::setData(
	const QModelIndex &index, const QVariant &value, int role)
{
	if (!isValidIndex(index))
	{
		return false;
	}

	try
	{
		if (role == Qt::CheckStateRole)
		{
			auto &item = getItem(index);
			item.setState(value.toBool());
			return true;
		}
	}
	catch (std::runtime_error &e)
	{
		qDebug() << "VerbEndModel::setData" << index << e.what();
	}

	return false;
}

QVariant VerbEndModel::headerData(
	int section, Qt::Orientation orientation, int role) const
{
	if (role == Qt::DisplayRole && orientation == Qt::Vertical)
	{
		switch (section)
		{
			case 0:
				return "Telefonat";
			case 1:
				return "Zaubertrick";
			case 2:
				return "Zauberregel";
			default:
				return {};
		}
	}

	return {};
}

void VerbEndModel::write(QJsonObject &json) const
{
	QJsonArray telefonat;
	m_telefonat.write(telefonat);
	json["Telefonat"] = telefonat;

	QJsonArray zaubertrick;
	m_zaubertrick.write(zaubertrick);
	json["Zaubertrick"] = zaubertrick;

	QJsonArray zauberregel;
	m_zauberregel.write(zauberregel);
	json["Zauberregel"] = zauberregel;
}

void VerbEndModel::read(const QJsonObject &json)
{
	if (json["Telefonat"].isArray())
	{
		m_telefonat.read(json["Telefonat"].toArray());
	}

	if (json["Zaubertrick"].isArray())
	{
		m_zaubertrick.read(json["Zaubertrick"].toArray());
	}

	if (json["Zauberregel"].isArray())
	{
		m_zauberregel.read(json["Zauberregel"].toArray());
	}
}

bool VerbEndModel::isValidIndex(const QModelIndex &index) const
{
	switch (index.row())
	{
		case 0:
			return index.column() < m_telefonat.size();
		case 1:
			return index.column() < m_zaubertrick.size();
		case 2:
			return index.column() < m_zauberregel.size();
		default:
			return false;
	}
}

CheckableItems &VerbEndModel::getItems(const QModelIndex &index)
{
	switch (index.row())
	{
		case 0:
			return m_telefonat;
		case 1:
			return m_zaubertrick;
		case 2:
			return m_zauberregel;
		default:
			break;
	}

	throw std::runtime_error("invalid index");
}

const CheckableItems &VerbEndModel::getItems(const QModelIndex &index) const
{
	switch (index.row())
	{
		case 0:
			return m_telefonat;
		case 1:
			return m_zaubertrick;
		case 2:
			return m_zauberregel;
		default:
			break;
	}

	throw std::runtime_error("invalid index");
}

CheckableItem &VerbEndModel::getItem(const QModelIndex &index)
{
	auto &items = getItems(index);
	if (index.column() < items.size())
	{
		return items.at(index.column());
	}

	throw std::runtime_error("invalid index");
}

const CheckableItem &VerbEndModel::getItem(const QModelIndex &index) const
{
	auto &items = getItems(index);
	if (index.column() < items.size())
	{
		return items.at(index.column());
	}

	throw std::runtime_error("invalid index");
}
