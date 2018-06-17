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
