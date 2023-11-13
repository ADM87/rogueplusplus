#pragma once

#include <ECS/ComponentTypeIds.h>
#include <ECS/IComponentBase.h>
#include <Math/Point2.h>

namespace rpp
{
    class TransformComponent
        : public IComponentBase
    {
    public:

        TransformComponent()
            : IComponentBase()
            , m_position()
        {}
        TransformComponent(const TransformComponent& _transform)
            : IComponentBase(_transform)
            , m_position(_transform.m_position)
        {}

        Point2Int Position()                            { return m_position; }
        void Position(const Point2Int& _position)       { m_position = _position; }

        void Update() override                          {}
        const std::string& GetTypeId() const override   { return ComponentTypeIds::TRANSFORM; }

    private:

        Point2Int m_position;
    };
}
