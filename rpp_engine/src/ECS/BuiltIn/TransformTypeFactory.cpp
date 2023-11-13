#include <ECS/BuiltIn/TransformComponent.h>
#include <ECS/BuiltIn/TransformTypeFactory.h>

using namespace rpp;

//
// TransformTypeFactory
//

IComponentBase* TransformTypeFactory::Create()
{
    return new TransformComponent();
}
