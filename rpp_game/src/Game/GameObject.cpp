#include <Game/GameObject.h>

#include <cassert>

using namespace rpp;

//
// GameObject
//

TransformComponent* const GameObject::Transform()
{
    if (m_transform == nullptr)
        m_transform = AddComponent<TransformComponent>("Transform");

    assert(("GameObject is missing its transform component", m_transform != nullptr));
    return m_transform;
}

RendererComponent* const GameObject::Renderer()
{
    if (m_renderer == nullptr)
        m_renderer = AddComponent<RendererComponent>("Renderer");

    assert(("GameObject is missing its renderer component", m_renderer != nullptr));
    return m_renderer;
}
