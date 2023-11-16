#pragma once

#include <Components/RendererComponent.h>
#include <Ecs/ComponentTypeFactory.h>

namespace rpp
{
    class RendererTypeFactory final
        : public ComponentTypeFactory
    {
    public:

        RendererTypeFactory(const std::string& _typeId)
            : ComponentTypeFactory(_typeId)
        {}

        Component* Create(Entity* _entity) override
        {
            return new RendererComponent(_entity, GetTypeId());
        }
    };
}
