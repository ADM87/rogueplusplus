#pragma once

#include <Ecs/Entity.h>

#include <string>

namespace rpp
{
    class Entity;
    class Component
    {
    public:

        Component(Entity* _entity, const std::string& _typeId)
            : m_entity(_entity)
            , m_typeId(_typeId)
        {}
        virtual ~Component();

        Entity* const GetEntity()       { return m_entity; }
        const std::string& GetTypeId()  { return m_typeId; }

    private:

        Entity*     m_entity;
        std::string m_typeId;
    };
}
