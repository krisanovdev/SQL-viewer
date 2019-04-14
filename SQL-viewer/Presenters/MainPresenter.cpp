#include <QSqlTableModel>
#include "MainPresenter.h"

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

void presenters::MainPresenter::PrepareInsert(const QString& tableName)
{

}

void presenters::MainPresenter::DeleteSelected(const std::vector<int>& rows, const QString& tableName)
{
    std::for_each(rows.cbegin(), rows.cend(), [this, &tableName](int row)
    {
        this->m_tables[tableName]->removeRow(row);
    });
    this->Refresh(tableName);
}

void presenters::MainPresenter::Refresh(const QString& tableName)
{
    static_cast<QSqlTableModel*>(m_tables[tableName])->select();
}

bool presenters::MainPresenter::Connect(const QString& host, int port, const QString& dbName, const QString& username, const QString& password)
{
    m_db.setHostName(host);
    m_db.setPort(port);
    m_db.setDatabaseName(dbName);
    m_db.setUserName(username);
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

        m_sqlView.reset(new SQLView(this));
    }

    return isSuccess;
}
