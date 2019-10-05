#pragma once

#include "Age.h"

#include <QAbstractTableModel>
#include <QPainter>

class TestResult
{
private:
    QString m_name;
    size_t m_points = 0;
    size_t m_pr = 0;

public:
    TestResult(const char* name)
        : m_name(name)
    {
    }

    void setPoints(const size_t& points)
    {
        m_points = points;
    }

    void setPR(const unsigned int& pr)
    {
        m_pr = pr;
    }

    const QString& name() const
    {
        return m_name;
    }

    const size_t points() const
    {
        return m_points;
    }

    const size_t pr() const
    {
        return m_pr;
    }
};

class ResultModel : public QAbstractTableModel
{
    Q_OBJECT

private:
    Age m_age;
    std::vector<TestResult> m_results;

public:
    ResultModel(QObject* parent);

    int rowCount(const QModelIndex& parent = QModelIndex()) const override;
    int columnCount(const QModelIndex& parent = QModelIndex()) const override;

    QVariant data(const QModelIndex& index, int role = Qt::DisplayRole) const override;

    QVariant headerData(int section, Qt::Orientation orientation,
                        int role = Qt::DisplayRole) const override;

    void setAge(const Age& age);
    void setPluralResult(unsigned int points);
    void setGenusResult(unsigned int points);
    void setVerbEndResult(unsigned int points);
    void setAkkusativResult(unsigned int points);
    void setDativResult(unsigned int points);
    void setV2Result(unsigned int points);
    void setSvkResult(unsigned int points);
    void setPassivResult(unsigned int points);
    void setGenitivResult(unsigned int points);

    void printTo(QPainter& painter) const;
};
