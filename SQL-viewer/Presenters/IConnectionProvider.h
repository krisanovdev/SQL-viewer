#pragma once
#include <QString>

namespace presenters
{
    class IConnectionProvider
    {
    public:
        virtual ~IConnectionProvider(){}
        virtual bool Connect(const QString& host, int port, const QString& dbName,
                             const QString& username, const QString& password) = 0;
    };
}
