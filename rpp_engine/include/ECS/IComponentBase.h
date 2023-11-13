#pragma once

#include <string>

namespace rpp
{
    class IComponentBase
    {
    public:

        IComponentBase()                                    = default;
        IComponentBase(const IComponentBase& _component)    = default;

        virtual void Update()                   = 0;
        virtual std::string GetTypeId() const   = 0;
    };
}
