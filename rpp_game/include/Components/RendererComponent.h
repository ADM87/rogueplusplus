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


    class RendererComponentFactory final
        : public ComponentTypeFactory
    {
    public:

        RendererComponentFactory()
            : ComponentTypeFactory(typeid(RendererComponent).name())
        {}

        Component* Create(Entity* _entity) override
        {
            return new RendererComponent(_entity, GetTypeId());
        }
    };
}
