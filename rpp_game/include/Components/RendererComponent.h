#pragma once

#include <Ecs/Component.h>
#include <Ecs/ComponentTypeFactory.h>

#include <Structures/Token.h>

namespace rpp
{
    class RendererComponent final
        : public Component
    {
    public:

        RendererComponent(Entity* _entity, const std::string& _typeId)
            : Component(_entity, _typeId)
            , m_tokenKey(0)
        {}

        const int& TokenKey()               { return m_tokenKey; }
        void TokenKey(const int& _tokenKey) { m_tokenKey = _tokenKey; }

    private:

        int m_tokenKey;
    };


    class RendererTypeFactory final
        : public ComponentTypeFactory
    {
    public:

        RendererTypeFactory(const std::string& _typeId)
            : ComponentTypeFactory(_typeId)
        {}

        Component* Create(Entity* _entity) override
        {
            return new RendererComponent(_entity, GetTypeId());
        }
    };
}
