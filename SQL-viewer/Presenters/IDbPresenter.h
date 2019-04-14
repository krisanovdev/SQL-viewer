#pragma once
#include <map>
#include <QAbstractItemModel>

namespace presenters
{
    using Tables = std::map<QString, QAbstractItemModel*>;

    class IDbPresenter
    {
    public:
        virtual ~IDbPresenter(){}
        virtual const Tables& GetTables() const = 0;
        virtual void PrepareInsert(const QString& tableName) = 0;
        virtual void DeleteSelected(const std::vector<int>& rows, const QString& tableName) = 0;
        virtual void Refresh(const QString& tableName) = 0;
    };
}
