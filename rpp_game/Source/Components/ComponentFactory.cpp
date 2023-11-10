#include <Components/ComponentFactory.h>
#include <Components/TransformComponent.h>

using namespace rpp;

//
// ComponentFactory
//

ComponentBase* ComponentFactory::Create(const RPPComponentTypes& _typeId)
{
    switch (_typeId)
    {
    case RPPComponentTypes::TRANSFORM_CMP:
        return new TransformComponent();
    }
    return nullptr;
}

void ComponentFactory::Destroy(ComponentBase* _component)
{
    if (_component == nullptr)
        return;

    delete _component;
    _component = nullptr;
}
