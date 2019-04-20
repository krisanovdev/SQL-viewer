#pragma once
#include <QWidget>
#include "ui_ConnectDialog.h"

namespace presenters
{
    class IConnectionProvider;
}

namespace views
{
    class ConnectDialog : public QWidget
    {
        Q_OBJECT

    public:
        explicit ConnectDialog(presenters::IConnectionProvider* provider, QWidget *parent = nullptr);

    private slots:
        void on_btn_connect_clicked();

    private:
        Ui::ConnectDialog m_ui;
        presenters::IConnectionProvider* m_provider;
    };
}

