#include <ECS/ComponentTypeIds.h>
#include <ECS/Entity.h>

using namespace rpp;

//
// Entity
//

Entity::Entity()
    : m_components()
{
    AddComponent(new TransformComponent());
}

Entity::~Entity()
{
    for (auto& kvp : m_components)
        delete kvp.second;

    m_components.clear();
}

Entity& Entity::AddComponent(IComponentBase* _component)
{
    if (m_components.find(_component->GetTypeId()) != m_components.end())
        return *this;

    m_components.insert({ _component->GetTypeId(), _component});
    return *this;
}

IComponentBase* Entity::GetComponent(const std::string _typeId)
{
    if (m_components.find(_typeId) == m_components.end())
        return nullptr;

    return m_components.at(_typeId);
}

TransformComponent* Entity::Transform()
{
    if (m_transform == nullptr)
        m_transform = dynamic_cast<TransformComponent*>(GetComponent(ComponentTypeIds::TRANSFORM));

    return m_transform;
}

void Entity::Update()
{
    if (m_components.size() == 0)
        return;
        
    for (auto& kvp : m_components)
    {
        if (kvp.second->Enabled())
            kvp.second->Update();
    }
}
