#include <Ecs/ComponentFactory.h>
#include <Ecs/Entity.h>

#include <cassert>

using namespace rpp;

//
// Entity
//

Entity::~Entity()
{
    for (auto& it : m_components)
        ComponentFactory::GetInstance().Destroy(it.second);

    m_components.clear();
}

void Entity::Update()
{
    if (m_components.size())
    {
        for (auto& kvp : m_components)
            kvp.second->Update();
    }
}

Component* Entity::AddComponent(const std::string& _typeId)
{
    Component* component = GetComponent(_typeId);

    if (component != nullptr)
        return component;

    component = ComponentFactory::GetInstance().Create(this, _typeId);
    
    if (component == nullptr)
        return nullptr;

    m_components.insert({ _typeId, component });
    return component;
}

Component* Entity::GetComponent(const std::string& _typeId)
{
    auto it = m_components.find(_typeId);

    if (it == m_components.end())
        return nullptr;

    return it->second;
}
