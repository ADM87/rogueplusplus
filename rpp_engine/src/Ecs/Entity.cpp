#include <Ecs/ComponentFactory.h>
#include <Ecs/Entity.h>

using namespace rpp;

//
// Entity
//

Entity::Entity(const std::vector<std::string>& _componentTypeIds)
    : m_components()
    , m_name("Entity")
{
    for (auto& id : _componentTypeIds)
        AddComponent(id);
}

Entity::Entity(const std::string& _name, const std::vector<std::string>& _componentTypeIds)
    : m_components()
    , m_name(_name)
{
    for (auto& id : _componentTypeIds)
        AddComponent(id);
}

Entity::~Entity()
{
    for (auto& it : m_components)
        ComponentFactory::GetInstance().Destroy(it.second);

    m_components.clear();
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
