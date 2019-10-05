#include "LateSkillsModel.h"

#include <regex>

LateSkillsModel::LateSkillsModel(QObject* parent)
    : PrintableModel(parent)
{
}

void LateSkillsModel::printTests(QPainter& painter) const
{
    painter.setFont(tableFont());
    painter.setPen(tablePen());

    auto width = painter.device()->width();
    auto height = 1.5 * painter.fontMetrics().lineSpacing();

    double headerWidth = headerWidthFactor() * width;
    double cellHeaderWidth = cellWidthFactor() * width;
    double cellWidth = 0.5 * cellHeaderWidth;
    double rowHeight = height;

    double x = 0;
    double y = 0;
    for (const auto& test : m_tests)
    {
        QString testName = QString::fromStdString(
            std::regex_replace(test.name().toStdString(), std::regex("\\s"), "\n"));

        drawTextSquare(painter, {0, y, headerWidth, 3 * rowHeight}, testName);

        const auto& items = test.items();

        x = headerWidth;
        for (unsigned int i = 0; i < items.size(); i += 2)
        {
            const auto& item = test.items().at(i);
            QString itemText = QString::fromStdString(item.getText()).split(" ").at(0);

            drawTextSquare(painter, {x, y, cellHeaderWidth, rowHeight}, itemText);

            x += cellHeaderWidth;
        }
        y += rowHeight;

        x = headerWidth;
        for (const auto& item : items)
        {
            drawTextSquare(painter, {x, y, cellWidth, rowHeight}, QString::number(item.value()));
            drawCheckSquare(painter, {x, y + rowHeight, cellWidth, rowHeight}, item.isChecked());

            x += cellWidth;
        }

        if (m_tests.size() > 1)
        {
            drawResultSquare(painter, y + rowHeight, true, test.getPoints());
        }

        y += 2 * rowHeight;
    }

    painter.translate(0, y + rowHeight);
}
