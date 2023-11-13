#pragma once

#include <Components/ComponentTypeIds.h>
#include <ECS/IComponentBase.h>

namespace rpp
{
    class WorldRendererComponent
        : public IComponentBase
    {
    public:

        WorldRendererComponent(const int& _layerKey, const int& _tokenKey)
            : IComponentBase()
            , m_layerKey(_layerKey)
            , m_tokenKey(_tokenKey)
        {}

        const int& TokenKey()               { return m_tokenKey; }
        void TokenKey(const int& _tokenKey) { m_tokenKey = _tokenKey; }

        void Update() override {}
        const std::string& GetTypeId() const override { return ComponentTypeIds::WORLD_RENDERER; }

    private:

        int m_layerKey;
        int m_tokenKey;
    };
}
