#pragma once

#include <Components/GameObjectComponent.h>
#include <Ecs/ComponentTypeFactory.h>

#include <type_traits>

namespace rpp
{
    class PlayerMovement
        : public GameObjectComponent
    {
    public:

        PlayerMovement(GameObject* _gameObject, const std::string& _typeId)
            : GameObjectComponent(_gameObject, _typeId)
        {}

        void Update() override;
    };

    class PlayerMovementComponentFactory
        : public ComponentTypeFactory
    {
    public:

        PlayerMovementComponentFactory()
            : ComponentTypeFactory(typeid(PlayerMovement).name())
        {}

        Component* Create(Entity* _entity) override
        {
            return new PlayerMovement(dynamic_cast<GameObject*>(_entity), GetTypeId());
        }
    };
}