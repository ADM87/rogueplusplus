#pragma once

#include <Ecs/Component.h>
#include <Ecs/ComponentTypeFactory.h>

#include <string>
#include <unordered_map>

namespace rpp
{
    class ComponentFactory final
    {
    public:

        static ComponentFactory& GetInstance()
        {
            static ComponentFactory instance;
            return instance;
        }

        ComponentFactory& Add(ComponentTypeFactory* _typeFactory);

        Component* Create(Entity* _entity, const std::string& _typeId);
        void Destroy(Component* _component);

    private:

        ComponentFactory()
            : m_typeFactories()
        {}

        std::unordered_map<std::string, ComponentTypeFactory*> m_typeFactories;
    };
}
