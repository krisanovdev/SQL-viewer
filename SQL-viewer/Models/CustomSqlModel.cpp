#include <QSqlIndex>
#include "CustomSqlModel.h"

models::CustomSqlModel::CustomSqlModel(QSqlDatabase db, const QString& tableName, QObject* parent)
    : QSqlTableModel(parent, db)
{
    this->setTable(tableName);
    this->select();
    const QSqlIndex primaryKey = this->primaryKey();

    for (int i = 0; i < primaryKey.count(); ++i)
    {
        m_privateKeyRows.push_back(this->fieldIndex(primaryKey.fieldName(i)));
    }
}

Qt::ItemFlags models::CustomSqlModel::flags(const QModelIndex& index) const
{
    return QSqlTableModel::flags(index);
    const Qt::ItemFlags flags = QSqlTableModel::flags(index);

    if (index.isValid() &&
        std::find(m_privateKeyRows.cbegin(), m_privateKeyRows.cend(), index.column()) != m_privateKeyRows.cend()
            && !index.row() == rowCount() - 1)
    {
        return flags & ~Qt::ItemIsEditable;
    }

    return flags;
}
