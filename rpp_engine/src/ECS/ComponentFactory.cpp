#include <ECS/ComponentFactory.h>
#include <ECS/EngineComponentTypeIds.h>
#include <ECS/BuiltIn/TransformTypeFactory.h>

using namespace rpp;

//
// ComponentFactory
//

ComponentFactory::ComponentFactory()
    : m_typeFactories()
{
    AddTypeFactory(EngineComponentTypeIds::TRANSFORM, new TransformTypeFactory());
}

void ComponentFactory::AddTypeFactory(const std::string _typeId, IComponentTypeFactory* _typeFactory)
{
    if (m_typeFactories.count(_typeId) == 0)
        m_typeFactories.insert({ _typeId, _typeFactory });
}

IComponentTypeFactory* ComponentFactory::GetTypeFactory(const std::string _typeId)
{
    if (m_typeFactories.count(_typeId) == 0)
        return nullptr;

    return m_typeFactories.at(_typeId);
}

IComponentBase* ComponentFactory::Create(const std::string _typeId)
{
    IComponentTypeFactory* typeFactory = GetTypeFactory(_typeId);

    if (typeFactory == nullptr)
        return nullptr;

    return typeFactory->Create();
}
