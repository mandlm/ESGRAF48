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
	using CheckableItems = std::map<size_t, CheckableItem>;

	CheckableItems m_tiere = {{0, {"Tiger"}}, {1, {"Bär"}}, {2, {"Katze"}},
		{3, {"Pferd"}}, {4, {"Gans"}}, {5, {"Elefant"}}, {6, {"Katze"}},
		{7, {"Hund"}}};

	CheckableItems m_futter = {{0, {"Salat"}}, {1, {"Fleisch"}},
		{2, {"Knocken"}}, {3, {"Banane"}}, {4, {"Apfel"}}, {5, {"Möhre"}},
		{6, {"Honig"}}, {7, {"Zucker"}}};

	CheckableItems m_zirkus = {
		{0, {"Kiste"}}, {1, {"Holz"}}, {2, {"Vorhang"}}, {3, {"Baum"}}};

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

private:
	bool isValidIndex(const QModelIndex &index) const;

	CheckableItems &getItems(const QModelIndex &index);
	const CheckableItems &getItems(const QModelIndex &index) const;

	CheckableItem &getItem(const QModelIndex &index);
	const CheckableItem &getItem(const QModelIndex &index) const;
};
