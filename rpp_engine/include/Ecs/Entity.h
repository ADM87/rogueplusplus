#pragma once

#include <Ecs/Component.h>

#include <string>
#include <type_traits>
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
        Entity(const std::vector<std::string> &_componentTypeIds);
        Entity(const std::string& _name, const std::vector<std::string>& _componentTypeIds);

        virtual ~Entity();

        template<typename TComponent>
        TComponent* AddComponent(const std::string& _typeId)
        {
            static_assert(std::is_base_of<Component, TComponent>::value);
            return dynamic_cast<TComponent*>(AddComponent(_typeId));
        }
        Component* AddComponent(const std::string& _typeId);

        template<typename TComponent>
        TComponent* GetComponent(const std::string& _typeId)
        {
            static_assert(std::is_base_of<Component, TComponent>::value);
            return dynamic_cast<TComponent*>(GetComponent(_typeId));
        }
        Component* GetComponent(const std::string& _typeId);

    private:

        std::string                                 m_name;
        std::unordered_map<std::string, Component*> m_components;
    };
}
