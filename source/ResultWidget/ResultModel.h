#pragma once

#include "Age.h"
#include "TestResult.h"

#include <QAbstractTableModel>
#include <QTextCursor>

class ResultModel : public QAbstractTableModel
{
	Q_OBJECT

private:
	Age m_age;
	std::vector<TestResult> m_results;

public:
	ResultModel(QObject *parent);

	int rowCount(const QModelIndex &parent = QModelIndex()) const override;
	int columnCount(const QModelIndex &parent = QModelIndex()) const override;

	QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;

	QVariant headerData(int section, Qt::Orientation orientation,
	                    int role = Qt::DisplayRole) const override;

	void setAge(const Age &age);
	void setPluralResult(unsigned int points);
	void setGenusResult(unsigned int points);
	void setVerbEndResult(unsigned int points);
	void setAkkusativResult(unsigned int points);
	void setDativResult(unsigned int points);
	void setV2Result(unsigned int points);
	void setSvkResult(unsigned int points);
	void setPassivResult(unsigned int points);
	void setGenitivResult(unsigned int points);

	void printTo(QTextCursor &cursor) const;
};
