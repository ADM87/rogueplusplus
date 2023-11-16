#pragma once

#include <Ecs/Component.h>

#include <string>

namespace rpp
{
    class ComponentTypeFactory
    {
    public:

        ComponentTypeFactory(const std::string& _typeId)
            : m_typeId(_typeId)
        {}

        virtual Component* Create(Entity* _entity) = 0;

        const std::string& GetTypeId() const { return m_typeId; }

    private:

        std::string m_typeId;
    };
}
