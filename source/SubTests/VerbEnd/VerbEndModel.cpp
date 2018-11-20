#include "VerbEndModel.h"

VerbEndModel::VerbEndModel(QObject *parent)
	: CheckableTestModel(parent)
{
	m_tests = { { "Telefonat",
					{ "Kausal", "Kausal", "Relativ", "Kausal",
						"Final", "Temporal", "Temporal" } },
		{ "Zaubertrick", { "Relativ", "Final", "Kausal", "Final",
							 "Temporal", "Kausal", "Temporal" } },
		{ "Zauberregel", { "Temporal", "Kausal", "Final", "Relativ",
							 "Temporal", "Relativ" } } };
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
