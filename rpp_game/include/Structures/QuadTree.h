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
            , m_root(nullptr)
            , m_gameObjects()
            , m_branches()
        {}
        QuadTreeNode(int _depth, int _capacity, const Rectangle& _bounds, QuadTreeNode* _root)
            : m_bounds(_bounds)
            , m_depth(_depth)
            , m_capacity(_capacity)
            , m_gameObjects()
            , m_branches()
            , m_root(_root)
        {}
        QuadTreeNode(const QuadTreeNode&_node)
            : m_bounds(_node.m_bounds)
            , m_depth(_node.m_depth)
            , m_capacity(_node.m_capacity)
            , m_gameObjects(_node.m_gameObjects)
            , m_branches(_node.m_branches)
            , m_root(_node.m_root)
        {}

        ~QuadTreeNode();

        bool Insert(GameObject* _transform);
        bool Erase(GameObject* _transform);
        bool Has(GameObject* _transform, bool _recursive = true);

        void Query(const Rectangle& _region, std::unordered_set<GameObject*>& _result);
        void Refresh(const Rectangle& _region);
        
    private:

        QuadTreeNode*                           m_root;
        Rectangle                               m_bounds;

        std::unordered_set<GameObject*> m_gameObjects;
        std::unordered_set<QuadTreeNode*>       m_branches;

        int m_depth;
        int m_capacity;

        void Subdivide();
    };
}
