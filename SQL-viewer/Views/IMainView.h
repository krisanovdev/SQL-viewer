#pragma once
#include <QString>

class QAbstractItemModel;

namespace views
{
    class IMainView
    {
    public:
        virtual ~IMainView(){}
        virtual void Start() = 0;
        virtual void AddLog(const QString& log) = 0;
        virtual void ShowSelectionResult(QAbstractItemModel* model) = 0;
    };
}
