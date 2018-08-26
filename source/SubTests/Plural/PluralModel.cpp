#include "PluralModel.h"

#include <QSize>

PluralModel::PluralModel(QObject *parent)
	: CheckableTestModel(parent)
{
	m_tests = { { "",
		{ "Fisch /-e/", "Banane /-n/", "Bonbon /-s/", "Ei /-er/", "Eimer /-ø/",
          "Korn UML+/-er/", "Nuss UML+/-e/", "Bär /-en/", "Apfel UML" } } };
}

QVariant PluralModel::data(const QModelIndex &index, int role) const
{
    if (role == Qt::SizeHintRole)
    {
        return QSize(180, 0);
    }

    return CheckableTestModel::data(index, role);
}

