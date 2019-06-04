#pragma once
#include "ui_MainView.h"
#include "SqlTableWidget.h"
#include "IMainView.h"

namespace presenters
{
    class IDbPresenter;
    struct ConnectionOptions;
}

namespace views
{
    class MainView : public QWidget, public IMainView
    {
        Q_OBJECT

    public:
        MainView(presenters::IDbPresenter* presenter, const presenters::ConnectionOptions& options, QWidget* parent = nullptr);
        virtual void Start() override;
        virtual void AddLog(const QString& log) override;
        virtual void ShowSelectionResult(QAbstractItemModel* model) override;

    private slots:
        void on_tables_doubleClicked(const QModelIndex& index);
        void on_btn_executeSql_clicked();

        void on_btn_clear_clicked();

    private:
        void OpenNewTable(const QString& tableName);

    private:
        Ui::MainView m_ui;
        presenters::IDbPresenter* m_presenter;
        std::map<QString, SqlTableWidget*> m_openedTables;
    };
}

