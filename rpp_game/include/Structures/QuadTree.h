#pragma once

#include <Components/TransformComponent.h>
#include <Math/Rectangle.h>

#include <unordered_set>

namespace rpp
{
    class QuadTreeNode final
    {
    public:

        QuadTreeNode()
            : m_bounds()
            , m_depth()
            , m_capacity()
            , m_parent(nullptr)
            , m_gameObjects()
            , m_branches()
        {}
        QuadTreeNode(int _depth, int _capacity, const Rectangle& _bounds, QuadTreeNode* _parent)
            : m_bounds(_bounds)
            , m_depth(_depth)
            , m_capacity(_capacity)
            , m_gameObjects()
            , m_branches()
            , m_parent(_parent)
        {}
        QuadTreeNode(const QuadTreeNode&_node)
            : m_bounds(_node.m_bounds)
            , m_depth(_node.m_depth)
            , m_capacity(_node.m_capacity)
            , m_gameObjects(_node.m_gameObjects)
            , m_branches(_node.m_branches)
            , m_parent(_node.m_parent)
        {}

        ~QuadTreeNode();

        bool Insert(GameObject* _gameObject);
        bool Reinsert(GameObject* _trasform);
        bool Erase(GameObject* _gameObject);

        void Query(const Rectangle& _region, std::unordered_set<GameObject*>& _result);
        void Refresh(const Rectangle& _region);
        void Refresh();

        const Rectangle& Bounds() { return m_bounds; }
        
    private:

        QuadTreeNode*                           m_parent;
        Rectangle                               m_bounds;

        std::unordered_set<GameObject*>         m_gameObjects;
        std::unordered_set<QuadTreeNode*>       m_branches;

        int m_depth;
        int m_capacity;

        void Subdivide();
    };
}
