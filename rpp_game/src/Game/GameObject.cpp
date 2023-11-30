#include <Game/GameObject.h>

#include <cassert>

using namespace rpp;

//
// GameObject
//

GameObject::GameObject()
    : Entity("GameObject")
    , m_transform(nullptr)
    , m_renderer(nullptr)
{
    Initialize();
}

GameObject::GameObject(const std::string& _name)
    : Entity(_name)
    , m_transform(nullptr)
    , m_renderer(nullptr)
{
    Initialize();
}

GameObject::~GameObject()
{
    m_transform = nullptr;
    m_renderer = nullptr;
}

void GameObject::Initialize()
{
    m_transform = AddComponent<TransformComponent>();
    m_renderer = AddComponent<RendererComponent>();
}
