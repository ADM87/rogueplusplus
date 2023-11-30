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

        GameObject();
        GameObject(const std::string& _name);
        ~GameObject() override;

        TransformComponent* const Transform()   { return m_transform; }
        RendererComponent*  const Renderer()    { return m_renderer; }

    private:

        TransformComponent* m_transform;
        RendererComponent*  m_renderer;

        void Initialize();
    };
}
