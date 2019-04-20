#include "ConnectDialog.h"
#include "Presenters/IConnectionProvider.h"

views::ConnectDialog::ConnectDialog(presenters::IConnectionProvider* provider, QWidget *parent)
    : QWidget(parent)
    , m_provider(provider)
{
    m_ui.setupUi(this);
    setFixedSize(size());
}

void views::ConnectDialog::on_btn_connect_clicked()
{
    presenters::ConnectionOptions opt;
    opt.db = m_ui.input_db->toPlainText();
    opt.host = m_ui.input_host->toPlainText();
    opt.username = m_ui.input_user->toPlainText();
    opt.port = m_ui.input_port->toPlainText().toInt();

    if (m_provider->Connect(opt, m_ui.input_password->toPlainText()))
    {
        deleteLater();
        close();
    }
}
