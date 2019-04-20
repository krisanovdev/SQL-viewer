#pragma once
#include <map>
#include <QAbstractItemModel>
#include "IConnectionProvider.h"

namespace presenters
{
    using Tables = std::map<QString, QAbstractItemModel*>;

    class IDbPresenter : public IConnectionProvider
    {
    public:
        virtual ~IDbPresenter(){}
        virtual const Tables& GetTables() const = 0;
        virtual void ExecuteSql(const QString& query) = 0;
        virtual void PrepareInsert(const QString& tableName) = 0;
        virtual void DeleteSelected(const std::vector<int>& rows, const QString& tableName) = 0;
        virtual void Refresh(const QString& tableName) = 0;
    };
}
