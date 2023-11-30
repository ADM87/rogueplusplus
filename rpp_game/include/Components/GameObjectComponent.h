#pragma once

#include <Ecs/Component.h>
#include <Game/GameObject.h>

namespace rpp
{
    class GameObjectComponent
        : public Component
    {
    public:

        GameObjectComponent(GameObject* _gameObject, const std::string& _typeId)
            : Component(_gameObject, _typeId)
            , m_gameObject(_gameObject)
        {}
        virtual ~GameObjectComponent() { m_gameObject = nullptr; }

    protected:

        GameObject* m_gameObject;
    };
}