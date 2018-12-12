#pragma once

#include "CheckableTestModel.h"
#include "VerbEndModel.pb.h"

#include <QTextCursor>

class VerbEndModel : public CheckableTestModel
{
	Q_OBJECT

public:
	VerbEndModel(QObject *parent);

	void write(ESGRAF48::VerbEndModel &model) const;
	void read(const ESGRAF48::VerbEndModel &model);

	unsigned int getCausalPoints() const;

protected:
	std::string getName() const override;

private slots:
	void modelChanged();

signals:
	void causalPointsChanged(unsigned int points);
};
