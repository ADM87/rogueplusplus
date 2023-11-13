#pragma once

#include <ECS/IComponentBase.h>

namespace rpp
{
    class IComponentTypeFactory
    {
    public:

        IComponentTypeFactory() = default;

        virtual IComponentBase* Create() = 0;
    };
}
