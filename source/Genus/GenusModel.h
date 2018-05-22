#pragma once

#include <string>

class CheckableItem
{
private:
    bool m_checked = false;
    std::string m_text;

public:
    CheckableItem(const std::string &text)
        : m_text(text)
    {
    }

    std::string getText() const
    {
        return m_text;
    }

    bool isChecked() const
    {
        return m_checked;
    }

    void setState(bool checked)
    {
        m_checked = checked;
    }
};

#include <QAbstractTableModel>
#include <QJsonObject>

class GenusModel : public QAbstractTableModel
{
	Q_OBJECT

private:
    std::map<size_t, CheckableItem> m_tiere =
    {
        {0, {"null"}},
        {1, {"eins"}}
    };

public:
	GenusModel(QObject *parent);
	int rowCount(const QModelIndex &parent = QModelIndex()) const override;
	int columnCount(const QModelIndex &parent = QModelIndex()) const override;
	QVariant data(
		const QModelIndex &index, int role = Qt::DisplayRole) const override;
	Qt::ItemFlags flags(const QModelIndex &index) const override;
	bool setData(const QModelIndex &index, const QVariant &value,
		int role = Qt::EditRole) override;

	QVariant headerData(int section, Qt::Orientation orientation,
		int role = Qt::DisplayRole) const;

	void write(QJsonObject &json) const;
	void read(const QJsonObject &json);
};
