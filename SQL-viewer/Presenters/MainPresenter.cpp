#include <QSqlTableModel>
#include "MainPresenter.h"
#include "Views/MainView.h"

presenters::MainPresenter::MainPresenter()
    : m_db(QSqlDatabase::addDatabase("QMYSQL"))
{

}

presenters::MainPresenter::~MainPresenter()
{
}

const presenters::Tables& presenters::MainPresenter::GetTables() const
{
    return m_tables;
}

void presenters::MainPresenter::ExecuteSql(const QString& query)
{

}

void presenters::MainPresenter::PrepareInsert(const QString& tableName)
{

}

void presenters::MainPresenter::DeleteSelected(const std::vector<int>& rows, const QString& tableName)
{
    std::for_each(rows.cbegin(), rows.cend(), [this, &tableName](int row)
    {
        m_tables[tableName]->removeRow(row);
    });
    this->Refresh(tableName);
}

void presenters::MainPresenter::Refresh(const QString& tableName)
{
    static_cast<QSqlTableModel*>(m_tables[tableName])->select();
}

bool presenters::MainPresenter::Connect(const ConnectionOptions& opt, const QString& password)
{
    m_db.setHostName(opt.host);
    m_db.setPort(opt.port);
    m_db.setDatabaseName(opt.db);
    m_db.setUserName(opt.username);
    m_db.setPassword(password);

    const bool isSuccess = m_db.open();

    if (isSuccess)
    {
        const QStringList& tables = m_db.tables();
        foreach (const QString& table, tables)
        {
            QSqlTableModel* model = new QSqlTableModel(this, m_db);
            model->setTable(table);
            m_tables.emplace(table, model);
        }

        m_sqlView.reset(new views::MainView(this));
        m_sqlView->Start();
    }

    return isSuccess;
}
