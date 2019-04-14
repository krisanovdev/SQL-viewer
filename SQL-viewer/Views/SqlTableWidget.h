#include <QWidget>
#include "ui_SqlTableWidget.h"

namespace views
{
    class SqlTableWidget : public QWidget
    {
        Q_OBJECT

    public:
        SqlTableWidget(const QString& tableName, QAbstractItemModel* model, QWidget *parent = nullptr);

    signals:
        void DeleteSelected(const std::vector<int>& rows, const QString& tableName);
        void PrepareInsert(const QString& tableName);
        void Refresh(const QString& tableName);

    private slots:
        void on_btn_deleteSelected_clicked();
        void on_btn_insert_clicked();
        void on_btn_refresh_clicked();

    private:
        Ui::SqlTableWidget m_ui;
    };
}

