#include <QApplication>
#include <Presenters/MainPresenter.h>

int main(int argc, char* argv[])
{
    QApplication app(argc, argv);
    presenters::MainPresenter presenter;
    presenter.Start();
    return app.exec();
}
