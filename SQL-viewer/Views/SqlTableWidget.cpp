#include <QModelIndexList>
#include <QModelIndex>
#include "SqlTableWidget.h"
#include "ui_SqlTableWidget.h"

views::SqlTableWidget::SqlTableWidget(const QString& tableName, QAbstractItemModel* model, QWidget *parent)
    : QWidget(parent)
{
    m_ui.setupUi(this);
    m_ui.lbl_tableName->setText(tableName);
    m_ui.tableView->setModel(model);
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

    emit DeleteSelected(deleted, m_ui.lbl_tableName->text());
}

void views::SqlTableWidget::on_btn_insert_clicked()
{
    emit PrepareInsert(m_ui.lbl_tableName->text());
    QAbstractItemModel* const model = m_ui.tableView->model();
    model->insertRow(model->rowCount());
    m_ui.tableView->selectRow(model->rowCount() - 1);
    m_ui.tableView->setFocus();
}

void views::SqlTableWidget::on_btn_refresh_clicked()
{
    emit Refresh(m_ui.lbl_tableName->text());
}
