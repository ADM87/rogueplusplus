#pragma once

#include <Components/TransformComponent.h>
#include <Components/RendererComponent.h>

#include <Ecs/Entity.h>

namespace rpp
{
    class GameObject final
        : public Entity
    {
    public:

        GameObject(const std::string& _name)
            : Entity(_name, { "Transform", "Renderer" })
            , m_transform(nullptr)
            , m_renderer(nullptr)
        {}

        TransformComponent* const Transform();
        RendererComponent*  const Renderer();

    private:

        TransformComponent* m_transform;
        RendererComponent*  m_renderer;
    };
}
