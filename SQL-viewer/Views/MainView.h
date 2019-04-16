#pragma once
#include "ui_MainView.h"
#include "SqlTableWidget.h"

namespace presenters
{
    class IDbPresenter;
}

namespace views
{
    class MainView : public QWidget
    {
        Q_OBJECT

    public:
        explicit MainView(presenters::IDbPresenter* presenter, QWidget *parent = nullptr);

    private slots:
        void on_tables_doubleClicked(const QModelIndex& index);
        void on_btn_executeSql_clicked();

    private:
        void OpenNewTable(const QString& tableName);

    private:
        Ui::MainView m_ui;
        presenters::IDbPresenter* m_presenter;
        std::map<QString, SqlTableWidget*> m_openedTables;
    };
}
