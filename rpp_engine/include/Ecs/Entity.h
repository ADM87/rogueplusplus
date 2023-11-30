#pragma once

#include <Ecs/Component.h>

#include <string>
#include <type_traits>
#include <typeinfo>
#include <unordered_map>

namespace rpp
{
    class Component;
    class Entity
    {
    public:

        Entity(const std::string& _name)
            : m_components()
            , m_name(_name)
        {}

        virtual ~Entity();
        
        void Update();

        template<typename TComponent>
        TComponent* AddComponent()
        {
            static_assert(std::is_base_of<Component, TComponent>::value);
            return dynamic_cast<TComponent*>(AddComponent(typeid(TComponent).name()));
        }
        Component* AddComponent(const std::string& _typeId);

        template<typename TComponent>
        TComponent* GetComponent()
        {
            static_assert(std::is_base_of<Component, TComponent>::value);
            return dynamic_cast<TComponent*>(GetComponent(typeid(TComponent).name()));
        }
        Component* GetComponent(const std::string& _typeId);

    private:

        std::string                                 m_name;
        std::unordered_map<std::string, Component*> m_components;
    };
}
