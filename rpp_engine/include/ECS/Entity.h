#pragma once

#include <ECS/IComponentBase.h>
#include <ECS/BuiltIn/TransformComponent.h>

#include <string>
#include <unordered_map>

namespace rpp
{
    class Entity final
    {
    public:

        Entity();
        ~Entity();

        Entity& AddComponent(IComponentBase* _component);

        IComponentBase* GetComponent(std::string _typeId);

        TransformComponent* Transform();

        virtual void Update();

    private:

        TransformComponent* m_transform;

        std::unordered_map<std::string, IComponentBase*> m_components;
    };
}
