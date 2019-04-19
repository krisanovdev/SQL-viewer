#include <QApplication>
#include <Presenters/MainPresenter.h>

int main(int argc, char* argv[])
{
    QApplication app(argc, argv);
    presenters::MainPresenter presenter;
    presenters::ConnectionOptions opt;
    opt.host = "localhost";
    opt.port = 3306;
    opt.username = "root";
    opt.db = "library";
    presenter.Connect(opt, "admin1!");
    return app.exec();
}
