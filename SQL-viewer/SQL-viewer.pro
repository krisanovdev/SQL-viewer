QT += core gui widgets sql
TARGET = SQL-viewer
TEMPLATE = app

DEFINES += QT_DEPRECATED_WARNINGS
CONFIG += c++14

SOURCES += \
        main.cpp \
    Models/CustomSqlModel.cpp \
    Views/SqlTableWidget.cpp \
    Presenters/MainPresenter.cpp \
    Views/MainView.cpp \
    main.cpp

HEADERS += \
    Models/CustomSqlModel.h \
    Presenters/IDbPresenter.h \
    Views/SqlTableWidget.h \
    Presenters/MainPresenter.h \
    Presenters/IConnectionProvider.h \
    Views/MainView.h \
    Views/IMainView.h

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

FORMS += \
    Views/SqlTableWidget.ui \
    Views/MainView.ui
