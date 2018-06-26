#include "PassivModel.h"

PassivModel::PassivModel(QObject *parent)
	: CheckableTestModel(parent)
{
	m_tests = {
        { "Passiv", { "Elefant", "Pferde", "Bälle", "Ball", "Fleisch" } }
	};
}
