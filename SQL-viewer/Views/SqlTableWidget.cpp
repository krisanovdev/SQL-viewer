#include <QModelIndexList>
#include <QModelIndex>
#include <QCloseEvent>
#include "SqlTableWidget.h"
#include "ui_SqlTableWidget.h"

views::SqlTableWidget::SqlTableWidget(const QString& tableName, QAbstractItemModel* model, QWidget *parent)
    : QWidget(parent)
    , m_tableName(tableName)
{
    m_ui.setupUi(this);
    m_ui.tableView->setModel(model);
    setWindowTitle(tableName);
    setFixedSize(size());
}

void views::SqlTableWidget::closeEvent(QCloseEvent* event)
{
    emit Closed(m_tableName);
    event->accept();
}

void views::SqlTableWidget::on_btn_deleteSelected_clicked()
{
    const QModelIndexList& list = m_ui.tableView->selectionModel()->selectedRows();
    std::vector<int> deleted;
    deleted.reserve(static_cast<uint32_t>(list.size()));

    foreach (const QModelIndex& row, list)
    {
        deleted.push_back(row.row());
    }

    emit DeleteSelected(deleted, m_tableName);
}

void views::SqlTableWidget::on_btn_insert_clicked()
{
    emit PrepareInsert(m_tableName);
    QAbstractItemModel* const model = m_ui.tableView->model();
    model->insertRow(model->rowCount());
    m_ui.tableView->selectRow(model->rowCount() - 1);
    m_ui.tableView->setFocus();
}

void views::SqlTableWidget::on_btn_refresh_clicked()
{
    emit Refresh(m_tableName);
}
