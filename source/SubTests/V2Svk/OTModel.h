#pragma once

#include "V2SvkModel.h"
#include "V2SvkModel.pb.h"

class OTModel : public V2SvkModel
{
    Q_OBJECT

public:
    OTModel(QObject* parent);

    unsigned int getV2Points() const override;
    unsigned int getSvkPoints() const override;

    void write(ESGRAF48::V2SvkModel& model) const override;
    void read(const ESGRAF48::V2SvkModel& model) override;

protected:
    void printHeader(QPainter&) const override{};

    std::set<int> v2Tests() const override;
    std::set<int> svkTests() const override;
};
