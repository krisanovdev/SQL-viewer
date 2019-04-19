#pragma once
#include <memory>
#include <QSqlDatabase>
#include "IDbPresenter.h"
#include "IConnectionProvider.h"

namespace views
{
    class IMainView;
}

namespace presenters
{
    class MainPresenter : public QObject, public IDbPresenter, public IConnectionProvider
    {
    public:
        MainPresenter();
        ~MainPresenter();
        virtual const Tables& GetTables() const override;
        virtual void ExecuteSql(const QString& query) override;
        virtual void PrepareInsert(const QString& tableName) override;
        virtual void DeleteSelected(const std::vector<int>& rows, const QString& tableName) override;
        virtual void Refresh(const QString& tableName) override;
        virtual bool Connect(const ConnectionOptions& opt, const QString& password) override;
        void Start();

    private:
        std::unique_ptr<views::IMainView> m_sqlView;
        QSqlDatabase m_db;
        Tables m_tables;
    };
}

