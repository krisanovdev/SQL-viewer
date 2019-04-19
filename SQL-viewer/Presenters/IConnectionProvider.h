#pragma once
#include <QString>

namespace presenters
{
    struct ConnectionOptions
    {
        QString host;
        int port;
        QString db;
        QString username;
    };

    class IConnectionProvider
    {
    public:
        virtual ~IConnectionProvider(){}
        virtual bool Connect(const ConnectionOptions& opt, const QString& password) = 0;
    };
}
