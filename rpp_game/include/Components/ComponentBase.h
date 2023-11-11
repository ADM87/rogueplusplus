#pragma once

#include <RPPConstants.h>

namespace rpp
{
    class ComponentBase
    {
    public:

        ComponentBase() = default;
        ComponentBase(const ComponentBase& _component) {}

        virtual ~ComponentBase() {}

        virtual const RPPComponentTypes& TypeId() = 0;
    };
}
