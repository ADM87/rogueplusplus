#pragma once

#include <ECS/IComponentBase.h>
#include <ECS/IComponentTypeFactory.h>

#include <string>
#include <unordered_map>

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

        void AddTypeFactory(const std::string _typeId, IComponentTypeFactory* _typeFactory);
        IComponentTypeFactory* GetTypeFactory(const std::string _typeId);

        IComponentBase* Create(const std::string _typeId);

    private:

        ComponentFactory();

        std::unordered_map<std::string, IComponentTypeFactory*> m_typeFactories;
    };
}