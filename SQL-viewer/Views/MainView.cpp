#include <QStringListModel>
#include <QDateTime>
#include "MainView.h"
#include "Presenters/IDbPresenter.h"

views::MainView::MainView(presenters::IDbPresenter* presenter, const presenters::ConnectionOptions& options, QWidget *parent)
    : QWidget(parent)
    , m_presenter(presenter)
{
    m_ui.setupUi(this);
    m_ui.lbl_db->setText(m_ui.lbl_db->text() + options.db);
    m_ui.lbl_user->setText(m_ui.lbl_user->text() + options.username);
    m_ui.lbl_host->setText(m_ui.lbl_host->text() + (options.host.isEmpty() ? "localhost" : options.host));
    m_ui.lbl_port->setText(m_ui.lbl_port->text() + QString::number(options.port ? options.port : 3306));
    QStringList list;
    foreach (const auto& item, presenter->GetTables())
    {
        list.append(item.first);
    }
    QAbstractItemModel* const model = new QStringListModel(list, m_ui.tables);
    m_ui.tables->setModel(model);
    setFixedSize(size());
}

void views::MainView::Start()
{
    this->show();
}

void views::MainView::AddLog(const QString& log)
{
    m_ui.logs->append(QDateTime::currentDateTime().toString() + " : " + log);
}

void views::MainView::ShowSelectionResult(QAbstractItemModel* model)
{
    QTableView* const selectionView = new QTableView(this);
    selectionView->setModel(model);
    selectionView->setFixedSize(this->size());
    selectionView->setWindowFlag(Qt::Dialog);
    selectionView->show();
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
        it->second->showNormal();
    }
}

void views::MainView::on_btn_executeSql_clicked()
{
    const QString& query = m_ui.queryEditor->toPlainText();
    m_presenter->ExecuteSql(query);
}

void views::MainView::on_btn_clear_clicked()
{
    m_ui.logs->clear();
}

void views::MainView::OpenNewTable(const QString& tableName)
{
    m_presenter->Refresh(tableName);
    QAbstractItemModel* const model = m_presenter->GetTables().at(tableName);
    SqlTableWidget* const widget = new SqlTableWidget(tableName, model);

    connect(widget, &SqlTableWidget::Closed, [this, widget](const QString& tableName)
    {
        m_openedTables.erase(tableName);
        widget->deleteLater();
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
