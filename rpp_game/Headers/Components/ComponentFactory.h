#pragma once

#include <RPPConstants.h>
#include <Components/ComponentBase.h>

namespace rpp
{
    class ComponentFactory final
    {
    public:

        static ComponentFactory& GetInstance()
        {
            static ComponentFactory instance;
            return instance;
        }

        ComponentBase* Create(const RPPComponentTypes& _typeId);
        void Destroy(ComponentBase* _component);

    private:

        ComponentFactory() = default;
    };
}