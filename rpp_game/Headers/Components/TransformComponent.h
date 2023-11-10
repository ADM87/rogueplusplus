#pragma once

#include <RPPConstants.h>
#include <Components/ComponentBase.h>
#include <Math/Point2.h>

namespace rpp
{
    class TransformComponent final
        : public ComponentBase
    {
    public:

        TransformComponent()
            : ComponentBase()
            , m_position()
        {}
        TransformComponent(const Point2Int& _position)
            : ComponentBase()
            , m_position(_position)
        {}
        TransformComponent(const TransformComponent& _transform)
            : ComponentBase(_transform)
            , m_position(_transform.m_position)
        {}
        
        Point2Int Position()                        { return m_position; }
        void Position(const Point2Int& _position)   { m_position = _position; }

        const RPPComponentTypes& TypeId() override   { return RPPComponentTypes::TRANSFORM_CMP; }

    private:

        Point2Int m_position;
    };
}
