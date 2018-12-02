#include "VerbEndModel.h"

#include <QTextTable>

VerbEndModel::VerbEndModel(QObject *parent)
    : CheckableTestModel(parent)
{
	m_tests = {
	    {"Telefonat", {"Kausal", "Kausal", "Relativ", "Kausal", "Final", "Temporal", "Temporal"}},
	    {"Zaubertrick", {"Relativ", "Final", "Kausal", "Final", "Temporal", "Kausal", "Temporal"}},
	    {"Zauberregel", {"Temporal", "Kausal", "Final", "Relativ", "Temporal", "Relativ"}}};
}

void VerbEndModel::write(ESGRAF48::VerbEndModel &model) const
{
	auto *telefonatModel = model.mutable_telefonat();
	if (telefonatModel != nullptr)
	{
		const auto &testItems = m_tests.at(0).items();

		telefonatModel->set_kausal1(testItems[0].isChecked());
		telefonatModel->set_kausal2(testItems[1].isChecked());
		telefonatModel->set_relativ(testItems[2].isChecked());
		telefonatModel->set_kausal3(testItems[3].isChecked());
		telefonatModel->set_final(testItems[4].isChecked());
		telefonatModel->set_temporal1(testItems[5].isChecked());
		telefonatModel->set_temporal2(testItems[6].isChecked());
	}

	auto *zaubertrickModel = model.mutable_zaubertrick();
	if (zaubertrickModel != nullptr)
	{
		const auto &testItems = m_tests.at(1).items();

		zaubertrickModel->set_relativ(testItems[0].isChecked());
		zaubertrickModel->set_final1(testItems[1].isChecked());
		zaubertrickModel->set_kausal1(testItems[2].isChecked());
		zaubertrickModel->set_final2(testItems[3].isChecked());
		zaubertrickModel->set_temporal1(testItems[4].isChecked());
		zaubertrickModel->set_kausal2(testItems[5].isChecked());
		zaubertrickModel->set_temporal2(testItems[6].isChecked());
	}

	auto *zauberregelModel = model.mutable_zauberregel();
	if (zauberregelModel != nullptr)
	{
		const auto &testItems = m_tests.at(2).items();

		zauberregelModel->set_temporal1(testItems[0].isChecked());
		zauberregelModel->set_kausal(testItems[1].isChecked());
		zauberregelModel->set_final(testItems[2].isChecked());
		zauberregelModel->set_relativ1(testItems[3].isChecked());
		zauberregelModel->set_temporal2(testItems[4].isChecked());
		zauberregelModel->set_relativ2(testItems[5].isChecked());
	}
}

void VerbEndModel::read(const ESGRAF48::VerbEndModel &model)
{
	const auto &telefonatModel = model.telefonat();
	{
		auto &testItems = m_tests.at(0).items();

		testItems[0].setState(telefonatModel.kausal1());
		testItems[1].setState(telefonatModel.kausal2());
		testItems[2].setState(telefonatModel.relativ());
		testItems[3].setState(telefonatModel.kausal3());
		testItems[4].setState(telefonatModel.final());
		testItems[5].setState(telefonatModel.temporal1());
		testItems[6].setState(telefonatModel.temporal2());
	}

	const auto &zaubertrickModel = model.zaubertrick();
	{
		auto &testItems = m_tests.at(1).items();

		testItems[0].setState(zaubertrickModel.relativ());
		testItems[1].setState(zaubertrickModel.final1());
		testItems[2].setState(zaubertrickModel.kausal1());
		testItems[3].setState(zaubertrickModel.final2());
		testItems[4].setState(zaubertrickModel.temporal1());
		testItems[5].setState(zaubertrickModel.kausal2());
		testItems[6].setState(zaubertrickModel.temporal2());
	}

	const auto &zauberregelModel = model.zauberregel();
	{
		auto &testItems = m_tests.at(2).items();

		testItems[0].setState(zauberregelModel.temporal1());
		testItems[1].setState(zauberregelModel.kausal());
		testItems[2].setState(zauberregelModel.final());
		testItems[3].setState(zauberregelModel.relativ1());
		testItems[4].setState(zauberregelModel.temporal2());
		testItems[5].setState(zauberregelModel.relativ2());
	}

	emit dataChanged(index(0, 0), index(rowCount() - 1, columnCount() - 1));
}

void VerbEndModel::printTo(QTextCursor &cursor) const
{
	cursor.insertBlock();

	QTextCharFormat headerFormat;
	headerFormat.setFontPointSize(12);
	cursor.insertText("Subtest 2: Verbendstellungsregel (VE)", headerFormat);

	QTextTableFormat tableFormat;
	tableFormat.setCellPadding(2);
	tableFormat.setCellSpacing(0);

	tableFormat.setColumnWidthConstraints({QTextLength(QTextLength::PercentageLength, 15),
	                                       QTextLength(QTextLength::PercentageLength, 9),
	                                       QTextLength(QTextLength::PercentageLength, 9),
	                                       QTextLength(QTextLength::PercentageLength, 9),
	                                       QTextLength(QTextLength::PercentageLength, 9),
	                                       QTextLength(QTextLength::PercentageLength, 9),
	                                       QTextLength(QTextLength::PercentageLength, 9),
	                                       QTextLength(QTextLength::PercentageLength, 9),
	                                       QTextLength(QTextLength::PercentageLength, 9),
	                                       QTextLength(QTextLength::PercentageLength, 2),
	                                       QTextLength(QTextLength::PercentageLength, 5),
	                                       QTextLength(QTextLength::PercentageLength, 1),
	                                       QTextLength(QTextLength::PercentageLength, 5)});

	QTextTable *table = cursor.insertTable(6, 13, tableFormat);
	table->mergeCells(0, 0, 2, 1);
	table->mergeCells(2, 0, 2, 1);
	table->mergeCells(4, 0, 2, 1);

	const char *emptyBox = "\u2610";
	//const char *checkBox = "\u2611";
	const char *checkBox = "x";

	cursor.insertText("Telefonat");
	cursor.movePosition(QTextCursor::NextCell);
	cursor.insertText("Kausal");
	cursor.movePosition(QTextCursor::NextCell);
	cursor.insertText("Kausal");
	cursor.movePosition(QTextCursor::NextCell);
	cursor.insertText("Relativ");
	cursor.movePosition(QTextCursor::NextCell);
	cursor.insertText("Kausal");
	cursor.movePosition(QTextCursor::NextCell);
	cursor.insertText("Final");
	cursor.movePosition(QTextCursor::NextCell);
	cursor.insertText("Temporal");
	cursor.movePosition(QTextCursor::NextCell);
	cursor.insertText("Temporal");
	cursor.movePosition(QTextCursor::NextRow);

	const auto &telTestItems = m_tests.at(0).items();
	cursor.insertText(telTestItems[0].isChecked() ? checkBox : emptyBox);
	cursor.movePosition(QTextCursor::NextCell);
	cursor.insertText(telTestItems[1].isChecked() ? checkBox : emptyBox);
	cursor.movePosition(QTextCursor::NextCell);
	cursor.insertText(telTestItems[2].isChecked() ? checkBox : emptyBox);
	cursor.movePosition(QTextCursor::NextCell);
	cursor.insertText(telTestItems[3].isChecked() ? checkBox : emptyBox);
	cursor.movePosition(QTextCursor::NextCell);
	cursor.insertText(telTestItems[4].isChecked() ? checkBox : emptyBox);
	cursor.movePosition(QTextCursor::NextCell);
	cursor.insertText(telTestItems[5].isChecked() ? checkBox : emptyBox);
	cursor.movePosition(QTextCursor::NextCell);
	cursor.insertText(telTestItems[6].isChecked() ? checkBox : emptyBox);
	cursor.movePosition(QTextCursor::NextCell);
	cursor.movePosition(QTextCursor::NextCell);
	cursor.movePosition(QTextCursor::NextCell);
	cursor.movePosition(QTextCursor::NextCell);
	cursor.movePosition(QTextCursor::NextCell);
	cursor.insertText(QString::number(m_tests.at(0).getPoints()));
	cursor.movePosition(QTextCursor::NextRow);

	cursor.insertText("Zaubertrick");
	cursor.movePosition(QTextCursor::NextCell);
	cursor.insertText("Relativ");
	cursor.movePosition(QTextCursor::NextCell);
	cursor.insertText("Final");
	cursor.movePosition(QTextCursor::NextCell);
	cursor.insertText("Kausal");
	cursor.movePosition(QTextCursor::NextCell);
	cursor.insertText("Final");
	cursor.movePosition(QTextCursor::NextCell);
	cursor.insertText("Temporal");
	cursor.movePosition(QTextCursor::NextCell);
	cursor.insertText("Kausal");
	cursor.movePosition(QTextCursor::NextCell);
	cursor.insertText("Temporal");
	cursor.movePosition(QTextCursor::NextRow);

	const auto &trickTestItems = m_tests.at(1).items();
	cursor.insertText(trickTestItems[0].isChecked() ? checkBox : emptyBox);
	cursor.movePosition(QTextCursor::NextCell);
	cursor.insertText(trickTestItems[1].isChecked() ? checkBox : emptyBox);
	cursor.movePosition(QTextCursor::NextCell);
	cursor.insertText(trickTestItems[2].isChecked() ? checkBox : emptyBox);
	cursor.movePosition(QTextCursor::NextCell);
	cursor.insertText(trickTestItems[3].isChecked() ? checkBox : emptyBox);
	cursor.movePosition(QTextCursor::NextCell);
	cursor.insertText(trickTestItems[4].isChecked() ? checkBox : emptyBox);
	cursor.movePosition(QTextCursor::NextCell);
	cursor.insertText(trickTestItems[5].isChecked() ? checkBox : emptyBox);
	cursor.movePosition(QTextCursor::NextCell);
	cursor.insertText(trickTestItems[6].isChecked() ? checkBox : emptyBox);
	cursor.movePosition(QTextCursor::NextCell);
	cursor.movePosition(QTextCursor::NextCell);
	cursor.movePosition(QTextCursor::NextCell);
	cursor.movePosition(QTextCursor::NextCell);
	cursor.movePosition(QTextCursor::NextCell);
	cursor.insertText(QString::number(m_tests.at(1).getPoints()));
	cursor.movePosition(QTextCursor::NextRow);

	cursor.insertText("Zauberregel");
	cursor.movePosition(QTextCursor::NextCell);
	cursor.insertText("Temporal");
	cursor.movePosition(QTextCursor::NextCell);
	cursor.insertText("Kausal");
	cursor.movePosition(QTextCursor::NextCell);
	cursor.insertText("Final");
	cursor.movePosition(QTextCursor::NextCell);
	cursor.insertText("Relativ");
	cursor.movePosition(QTextCursor::NextCell);
	cursor.insertText("Temporal");
	cursor.movePosition(QTextCursor::NextCell);
	cursor.insertText("Relativ");
	cursor.movePosition(QTextCursor::NextRow);

	const auto &regelTestItems = m_tests.at(2).items();
	cursor.insertText(regelTestItems[0].isChecked() ? checkBox : emptyBox);
	cursor.movePosition(QTextCursor::NextCell);
	cursor.insertText(regelTestItems[1].isChecked() ? checkBox : emptyBox);
	cursor.movePosition(QTextCursor::NextCell);
	cursor.insertText(regelTestItems[2].isChecked() ? checkBox : emptyBox);
	cursor.movePosition(QTextCursor::NextCell);
	cursor.insertText(regelTestItems[3].isChecked() ? checkBox : emptyBox);
	cursor.movePosition(QTextCursor::NextCell);
	cursor.insertText(regelTestItems[4].isChecked() ? checkBox : emptyBox);
	cursor.movePosition(QTextCursor::NextCell);
	cursor.insertText(regelTestItems[5].isChecked() ? checkBox : emptyBox);
	cursor.movePosition(QTextCursor::NextCell);
	cursor.movePosition(QTextCursor::NextCell);
	cursor.movePosition(QTextCursor::NextCell);
	cursor.movePosition(QTextCursor::NextCell);
	cursor.movePosition(QTextCursor::NextCell);
	cursor.movePosition(QTextCursor::NextCell);
	cursor.insertText(QString::number(m_tests.at(2).getPoints()));

	cursor.movePosition(QTextCursor::NextBlock);
}

