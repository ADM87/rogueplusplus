#pragma once

#include <Ecs/Component.h>
#include <Ecs/ComponentTypeFactory.h>

#include <Math/Point2.h>

namespace rpp
{
    class TransformComponent final
        : public Component
    {
    public:

        TransformComponent(Entity* _entity, const std::string& _typeId)
            : Component(_entity, _typeId)
        {}

        Point2Int Position()                        { return m_position; }
        void Position(const Point2Int& _position)   { m_position = _position; }

    private:

        Point2Int m_position;
    };

    class TransformComponentFactory
        : public ComponentTypeFactory
    {
    public:

        TransformComponentFactory()
            : ComponentTypeFactory(typeid(TransformComponent).name())
        {}

        Component* Create(Entity* _entity) override
        {
            return new TransformComponent(_entity, GetTypeId());
        }
    };
}