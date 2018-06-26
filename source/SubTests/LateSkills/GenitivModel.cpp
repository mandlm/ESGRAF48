#include "GenitivModel.h"

GenitivModel::GenitivModel(QObject *parent)
	: CheckableTestModel(parent)
{
	m_tests = {
        { "Genitiv Präpositionen", { "anstelle", "außerhalb", "mithilfe" } },
        { "Attributierung", { "Schuhe", "Zauberstab", "Hut", "Brille", "Gürtel" } },
    };
}
