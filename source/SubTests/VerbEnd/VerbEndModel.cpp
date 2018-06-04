#include "VerbEndModel.h"

VerbEndModel::VerbEndModel(QObject *parent)
	: CheckableTestModel(parent)
{
	m_tests = { { "Telefonat",
					{ "Kausal (1)", "Kausal (2)", "Relativ", "Kausal (3)",
						"Final", "Temporal (1)", "Temporal (2)" } },
		{ "Zaubertrick", { "Relativ", "Final (1)", "Kausal (1)", "Final (2)",
							 "Temporal (1)", "Kausal (2)", "Temporal (2)" } },
		{ "Zauberregel", { "Temporal (1)", "Kausal", "Final", "Relativ (1)",
							 "Temporal (2)", "Relativ (2)" } } };
}
