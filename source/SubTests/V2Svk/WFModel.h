#pragma once

#include "V2SvkModel.h"
#include "V2SvkModel.pb.h"

class WFModel : public V2SvkModel
{
    Q_OBJECT

public:
    WFModel(QObject* parent);

    unsigned int getV2Points() const override;
    unsigned int getSvkPoints() const override;

    void write(ESGRAF48::V2SvkModel& model) const override;
    void read(const ESGRAF48::V2SvkModel& model) override;

protected:
    std::set<int> v2Tests() const override;
    std::set<int> svkTests() const override;

    bool isValidIndex(const QModelIndex& index) const override;
};
