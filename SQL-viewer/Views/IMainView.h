#pragma once

namespace views
{
    class IMainView
    {
    public:
        virtual ~IMainView(){}
        virtual void Start() = 0;
    };
}
