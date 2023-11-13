#include <ECS/ComponentFactory.h>
#include <ECS/EngineComponentTypeIds.h>
#include <ECS/Entity.h>

using namespace rpp;

//
// Entity
//

Entity::Entity()
    : m_components()
{
    AddComponent(EngineComponentTypeIds::TRANSFORM);
}

Entity::~Entity()
{
    for (auto& kvp : m_components)
        delete kvp.second;

    m_components.clear();
}

IComponentBase* Entity::AddComponent(const std::string _typeId)
{
    IComponentBase* component = GetComponent(_typeId);
    
    if (component != nullptr)
        return component;

    component = ComponentFactory::GetInstance().Create(_typeId);
    m_components.insert({ _typeId, component });

    return component;
}

IComponentBase* Entity::GetComponent(const std::string _typeId)
{
    if (m_components.count(_typeId) == 0)
        return nullptr;

    return m_components.at(_typeId);
}

TransformComponent* Entity::Transform()
{
    if (m_transform == nullptr)
        m_transform = dynamic_cast<TransformComponent*>(GetComponent(EngineComponentTypeIds::TRANSFORM));

    return m_transform;
}

void Entity::Update()
{
    if (m_components.size() == 0)
        return;
        
    for (auto& kvp : m_components)
        kvp.second->Update();
}