#include "PluralModel.h"

#include <QSize>

#include <regex>

PluralModel::PluralModel(QObject* parent)
    : PrintableModel(parent)
{
    m_title = "Subtest 5: Plural";

    m_tests = {{"Plural",
                {"Fisch /-e/", "Banane /-n/", "Bonbon /-s/", "Ei /-er/", "Eimer /-ø/",
                 "Korn UML+/-er/", "Nuss UML+/-e/", "Bär /-en/", "Apfel UML"}}};
}

void PluralModel::read(const ESGRAF48::PluralModel& model)
{
    auto& testItems = m_tests.at(0).items();

    testItems[0].setState(model.fisch());
    testItems[1].setState(model.banane());
    testItems[2].setState(model.bonbon());
    testItems[3].setState(model.ei());
    testItems[4].setState(model.eimer());
    testItems[5].setState(model.korn());
    testItems[6].setState(model.nuss());
    testItems[7].setState(model.baer());
    testItems[8].setState(model.apfel());

    emit dataChanged(index(0, 0), index(rowCount() - 1, columnCount() - 1));
}

void PluralModel::write(ESGRAF48::PluralModel& model) const
{
    const auto& testItems = m_tests.at(0).items();

    model.set_fisch(testItems[0].isChecked());
    model.set_banane(testItems[1].isChecked());
    model.set_bonbon(testItems[2].isChecked());
    model.set_ei(testItems[3].isChecked());
    model.set_eimer(testItems[4].isChecked());
    model.set_korn(testItems[5].isChecked());
    model.set_nuss(testItems[6].isChecked());
    model.set_baer(testItems[7].isChecked());
    model.set_apfel(testItems[8].isChecked());
}

void PluralModel::printTests(QPainter& painter) const
{
    painter.setFont(tableFont());
    painter.setPen(tablePen());

    auto width = painter.device()->width();
    auto height = 1.5 * painter.fontMetrics().lineSpacing();

    double headerWidth = headerWidthFactor() * width;
    double cellWidth = cellWidthFactor() * width;
    double rowHeight = height;

    double x = 0;
    double y = 0;
    for (const auto& test : m_tests)
    {
        drawTextSquare(painter, {0, y, headerWidth, 3 * rowHeight}, test.name());
        x = headerWidth;

        for (const auto& item : test.items())
        {
            QString itemText =
                QString::fromStdString(std::regex_replace(item.getText(), std::regex("\\s"), "\n"));

            drawTextSquare(painter, {x, y, cellWidth, 2 * rowHeight}, itemText);
            drawCheckSquare(painter, {x, y + 2 * rowHeight, cellWidth, rowHeight},
                            item.isChecked());

            x += cellWidth;
        }
        y += 2 * rowHeight;
    }

    painter.translate(0, y + 2 * rowHeight);
}
