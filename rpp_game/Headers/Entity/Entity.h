#pragma once

#include <RPPConstants.h>
#include <Components/ComponentBase.h>
#include <Components/TransformComponent.h>
#include <Math/Point2.h>

#include <map>

namespace rpp
{
    class Entity final
    {
    public:

        Entity(const RPPTokens& _token)
            : m_layer(RPPLayers::DEFAULT_LAYER)
            , m_token(_token)
        { Initialize(); }
        Entity(const RPPTokens& _token, const RPPLayers& _layer)
            : m_layer(_layer)
            , m_token(_token)
        { Initialize(); }
        ~Entity();

        const RPPLayers& Layer() { return m_layer; }
        const RPPTokens& Token() { return m_token; }

        void AddComponent(const RPPComponentTypes& _typeId);
        void RemoveComponent(const RPPComponentTypes& _typeId);

        ComponentBase* GetComponent(const RPPComponentTypes& _typeId);
        
        TransformComponent* Transform();

    private:

        RPPLayers m_layer;
        RPPTokens m_token;

        std::map<RPPComponentTypes, ComponentBase*> m_components;

        void Initialize();
    };
}
