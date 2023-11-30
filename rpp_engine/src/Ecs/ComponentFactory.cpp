#include <Ecs/ComponentFactory.h>

#include <cassert>

using namespace rpp;

//
// ComponentFactory
//

ComponentFactory& ComponentFactory::Add(ComponentTypeFactory* _typeFactory)
{
    assert(("Provided type factory callnot be null", _typeFactory != nullptr));

    auto it = m_typeFactories.find(_typeFactory->GetTypeId());
    assert(("Component factory type already registered", it == m_typeFactories.end()));

    m_typeFactories.insert({ _typeFactory->GetTypeId(), _typeFactory });
    return *this;
}

Component* ComponentFactory::Create(Entity* _entity, const std::string& _typeId)
{
    auto it = m_typeFactories.find(_typeId);

    if (it == m_typeFactories.end())
        return nullptr;

    return it->second->Create(_entity);
}

void ComponentFactory::Destroy(Component* _component)
{
    if (_component == nullptr)
        return;

    delete _component;
    _component = nullptr;
}
