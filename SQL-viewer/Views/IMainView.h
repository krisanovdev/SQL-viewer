#pragma once
#include <QString>

namespace views
{
    class IMainView
    {
    public:
        virtual ~IMainView(){}
        virtual void Start() = 0;
        virtual void AddLog(const QString& log) = 0;
    };
}
