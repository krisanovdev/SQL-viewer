#include "MainView.h"
#include "Presenters/IDbPresenter.h"

views::MainView::MainView(presenters::IDbPresenter* presenter, QWidget *parent)
    : QWidget(parent)
    , m_presenter(presenter)
{
    m_ui.setupUi(this);
}

void views::MainView::on_tables_doubleClicked(const QModelIndex& index)
{
    const QString& tableName = m_ui.tables->model()->data(index).toString();
    const auto it = m_openedTables.find(tableName);
    if (it == m_openedTables.end())
    {
        OpenNewTable(tableName);
    }
    else
    {
        it->second->setFocus();
    }
}

void views::MainView::on_btn_executeSql_clicked()
{
    const QString& query = m_ui.queryEditor->toPlainText();
    m_presenter->ExecuteSql(query);
}

void views::MainView::OpenNewTable(const QString& tableName)
{
    QAbstractItemModel* const model = m_presenter->GetTables().at(tableName);
    SqlTableWidget* const widget = new SqlTableWidget(tableName, model, this);

    connect(widget, &QObject::destroyed, [this, &tableName]()
    {
        m_openedTables.erase(tableName);
    });

    connect(widget, &SqlTableWidget::DeleteSelected, [this](const std::vector<int>& rows, const QString& tableName)
    {
        m_presenter->DeleteSelected(rows, tableName);
    });

    connect(widget, &SqlTableWidget::Refresh, [this](const QString& tableName)
    {
        m_presenter->Refresh(tableName);
    });

    m_openedTables.emplace(tableName, widget);
    widget->show();
    widget->setFocus();
}
