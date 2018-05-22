#include "GenusModel.h"

#include <QDebug>

GenusModel::GenusModel(QObject *parent)
	: QAbstractTableModel(parent)
{
}

int GenusModel::rowCount(const QModelIndex &parent) const
{
	return 3;
}

int GenusModel::columnCount(const QModelIndex &parent) const
{
	return 8;
}

QVariant GenusModel::data(const QModelIndex &index, int role) const
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
        qDebug() << "GenusModel::data" << index << e.what();
    }

    return {};
}

Qt::ItemFlags GenusModel::flags(const QModelIndex &index) const
{
    if (isValidIndex(index))
    {
        return Qt::ItemIsEnabled | Qt::ItemIsUserCheckable;
    }

    return Qt::NoItemFlags;
}

bool GenusModel::setData(
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
        qDebug() << "GenusModel::setData" << index << e.what();
    }

    return false;
}

QVariant GenusModel::headerData(
	int section, Qt::Orientation orientation, int role) const
{
    if (role == Qt::DisplayRole && orientation == Qt::Vertical)
    {
        switch (section)
        {
            case 0:
                return "Tiere";
            case 1:
                return "Futter";
            case 2:
                return "Zirkus";
            default:
                return {};
        }
    }

	return {};
}

void GenusModel::write(QJsonObject &json) const
{
}

void GenusModel::read(const QJsonObject &json)
{
}

bool GenusModel::isValidIndex(const QModelIndex &index) const
{
    switch (index.row())
    {
    case 0:
        return m_tiere.find(index.column()) != m_tiere.end();
    case 1:
        return m_futter.find(index.column()) != m_futter.end();
    case 2:
        return m_zirkus.find(index.column()) != m_zirkus.end();
    default:
        return false;
    }
}

GenusModel::CheckableItems &GenusModel::getItems(const QModelIndex &index)
{
    switch (index.row())
    {
    case 0:
        return m_tiere;
    case 1:
        return m_futter;
    case 2:
        return m_zirkus;
    default:
        break;
    }

    throw std::runtime_error("invalid index");
}

const GenusModel::CheckableItems &GenusModel::getItems(const QModelIndex &index) const
{
    switch (index.row())
    {
    case 0:
        return m_tiere;
    case 1:
        return m_futter;
    case 2:
        return m_zirkus;
    default:
        break;
    }

    throw std::runtime_error("invalid index");
}

CheckableItem &GenusModel::getItem(const QModelIndex &index)
{
    auto &items = getItems(index);
    auto entry = items.find(index.column());
    if (entry != items.end())
    {
        return entry->second;
    }

    throw std::runtime_error("invalid index");
}

const CheckableItem &GenusModel::getItem(const QModelIndex &index) const
{
    auto &items = getItems(index);
    auto entry = items.find(index.column());
    if (entry != items.end())
    {
        return entry->second;
    }

    throw std::runtime_error("invalid index");
}
