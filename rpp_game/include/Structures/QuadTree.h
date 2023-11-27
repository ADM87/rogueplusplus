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
            , m_entries()
            , m_branches()
        {}
        QuadTreeNode(int _depth, int _capacity, const Rectangle& _bounds, QuadTreeNode* _root)
            : m_bounds(_bounds)
            , m_depth(_depth)
            , m_capacity(_capacity)
            , m_entries()
            , m_branches()
            , m_root(_root)
        {}
        QuadTreeNode(const QuadTreeNode&_node)
            : m_bounds(_node.m_bounds)
            , m_depth(_node.m_depth)
            , m_capacity(_node.m_capacity)
            , m_entries(_node.m_entries)
            , m_branches(_node.m_branches)
            , m_root(_node.m_root)
        {}

        ~QuadTreeNode();

        bool Insert(TransformComponent* _transform);
        bool Erase(TransformComponent* _transform);
        bool Has(TransformComponent* _transform, bool _recursive = true);

        void Query(const Rectangle& _region, std::unordered_set<TransformComponent*>& _result);
        void Refresh(const Rectangle& _region);
        
    private:

        QuadTreeNode*                           m_root;
        Rectangle                               m_bounds;

        std::unordered_set<TransformComponent*> m_entries;
        std::unordered_set<QuadTreeNode*>       m_branches;

        int m_depth;
        int m_capacity;

        void Subdivide();
    };
}
