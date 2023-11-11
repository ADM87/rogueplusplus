#include <RPPConstants.h>
#include <Components/ComponentFactory.h>
#include <Entity/Entity.h>

using namespace rpp;

//
// GameObject
//

Entity::~Entity()
{
    RemoveComponent(RPPComponentTypes::TRANSFORM_CMP);
}

void Entity::Initialize()
{
    AddComponent(RPPComponentTypes::TRANSFORM_CMP);
}

void Entity::AddComponent(const RPPComponentTypes& _typeId)
{
    if (m_components.count(_typeId) == 0)
    {
        ComponentBase* component = ComponentFactory::GetInstance().Create(_typeId);

        if (component == nullptr)
            return;

        m_components.insert({ _typeId, component });
    }
}

void Entity::RemoveComponent(const RPPComponentTypes& _typeId)
{
    if (m_components.count(_typeId) == 0)
        return;

    ComponentBase* component = m_components.at(_typeId);
    m_components.erase(_typeId);

    ComponentFactory::GetInstance().Destroy(component);
}

ComponentBase* Entity::GetComponent(const RPPComponentTypes& _typeId)
{
    if (m_components.count(_typeId) == 0)
        return nullptr;

    return m_components.at(_typeId);
}

TransformComponent* Entity::Transform()
{
    ComponentBase* component = GetComponent(RPPComponentTypes::TRANSFORM_CMP);

    if (component == nullptr)
        return nullptr;

    return dynamic_cast<TransformComponent*>(component);
}
