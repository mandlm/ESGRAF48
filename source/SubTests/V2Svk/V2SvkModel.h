#pragma once

#include "CheckableTestModel.h"
#include "V2SvkModel.pb.h"

#include <QTextCursor>

class V2SvkModel : public CheckableTestModel
{
	Q_OBJECT

public:
	V2SvkModel(QObject *parent);

	unsigned int getV2Points() const;
	unsigned int getSvkPoints() const;

	void write(ESGRAF48::V2SvkModel &model) const;
	void read(const ESGRAF48::V2SvkModel &model);

protected:
	bool isValidIndex(const QModelIndex &index) const override;

	std::string getName() const override;
	void printTableTo(QTextCursor &cursor) const override;
	void printSummaryTo(QTextCursor &cursor) const override;
};
