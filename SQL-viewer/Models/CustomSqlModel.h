#pragma once
#include <QSqlTableModel>

namespace models
{
    class CustomSqlModel : public QSqlTableModel
    {
    public:
        CustomSqlModel(QSqlDatabase db, const QString& tableName, QObject* parent = nullptr);

    protected:
        virtual Qt::ItemFlags flags(const QModelIndex& index) const override;

    private:
        std::vector<int> m_privateKeyRows;
    };
}
