#pragma once

#include <Components/TransformComponent.h>
#include <Ecs/ComponentTypeFactory.h>

namespace rpp
{
    class TransformTypeFactory
        : public ComponentTypeFactory
    {
    public:

        TransformTypeFactory(const std::string& _typeId)
            : ComponentTypeFactory(_typeId)
        {}

        Component* Create(Entity* _entity) override
        {
            return new TransformComponent(_entity, GetTypeId());
        }
    };
}