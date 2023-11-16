#include <Ecs/Component.h>

using namespace rpp;

//
// Component
//

Component::~Component()
{
    m_entity = nullptr;
}
