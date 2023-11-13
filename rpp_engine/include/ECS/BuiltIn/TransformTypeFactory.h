#pragma once

#include <ECS/IComponentTypeFactory.h>
#include <ECS/BuiltIn/TransformComponent.h>

namespace rpp
{
    class TransformTypeFactory final
        : public IComponentTypeFactory
    {
    public:

        TransformTypeFactory()
            : IComponentTypeFactory()
        {}

        virtual IComponentBase* Create() override;
    };
}