#include <Structures/QuadTree.h>

#include <algorithm>
#include <cassert>

using namespace rpp;

#pragma region TreeUtility

bool InsertOnBranch(QuadTreeNode* _branch, TransformComponent* _transform)
{
    if (_branch == nullptr)
        return false;

    return _branch->Insert(_transform);
}

bool RemoveFromBranch(QuadTreeNode* _branch, TransformComponent* _transform)
{
    if (_branch == nullptr)
        return false;

    return _branch->Erase(_transform);
}

bool BranchContains(QuadTreeNode* _node, TransformComponent* _transform, bool _recursive)
{
    if (_node == nullptr)
        return false;

    return _node->Has(_transform, _recursive);
}

void DistributeToBranch(QuadTreeNode* _branch, std::unordered_set<TransformComponent*>& _enteries)
{
    if (_branch == nullptr || _enteries.size() == 0)
        return;

    std::unordered_set<TransformComponent*> container(_enteries);

    for (auto& entry : container)
    {
        if (_branch->Insert(entry))
            _enteries.erase(entry);
    }
}

void QueryBranch(QuadTreeNode* _branch, const Rectangle& _region, std::unordered_set<TransformComponent*>& _result)
{
    if (_branch == nullptr)
        return;

    _branch->Query(_region, _result);
}

void RefreshBranch(QuadTreeNode* _branch, const Rectangle& _region)
{
    if (_branch == nullptr)
        return;

    _branch->Refresh(_region);
}

void PruneBranch(QuadTreeNode* _branch)
{
    if (_branch == nullptr)
        return;

    delete _branch;
    _branch = nullptr;
}

#pragma endregion

//
// QuadTreeNode
//

QuadTreeNode::~QuadTreeNode()
{
    // Don't delete the root!
    m_root = nullptr;

    for (auto& branch : m_branches)
        PruneBranch(branch);

    m_branches.clear();
    m_entries.clear();
}

bool QuadTreeNode::Insert(TransformComponent* _transform)
{
    if (_transform == nullptr || !m_bounds.Contains(_transform->Position()))
        return false;

    // If depth is 0, the node cannot be subdivided so allow it to overflow.
    if (m_depth == 0 || (m_branches.size() == 0 && m_entries.size() < m_capacity))
    {
        m_entries.insert(_transform);
        return true;
    }

    if (m_branches.size() == 0)
    {
        Subdivide();
        for (auto& branch : m_branches)
            DistributeToBranch(branch, m_entries);

        assert(!m_entries.size() && "Failed to distribute quad tree entries to child branches");
    }

    for (auto& branch : m_branches)
    {
        if (InsertOnBranch(branch, _transform))
            return true;
    }

    return false;
}

bool QuadTreeNode::Erase(TransformComponent* _transform)
{
    return false;
}

bool QuadTreeNode::Has(TransformComponent* _transform, bool _recursive)
{
    return false;
}

void QuadTreeNode::Query(const Rectangle& _region, std::unordered_set<TransformComponent*>& _result)
{
    if (!_region.Overlaps(m_bounds))
        return;

    if (m_branches.size())
    {
        for (auto& it : m_branches)
            QueryBranch(it, _region, _result);

        return;
    }

    if (m_entries.size())
    {
        for (auto& it : m_entries)
        {
            if (_region.Contains(it->Position()))
                _result.insert(it);
        }
    }
}

void QuadTreeNode::Refresh(const Rectangle& _region)
{
    if (!_region.Overlaps(m_bounds))
        return;

    if (m_branches.size() > 0)
    {
        for (auto& branch : m_branches)
            RefreshBranch(branch, _region);
    }

    if (m_entries.size() > 0)
    {
        std::unordered_set<TransformComponent*> reinsert;

        for (auto& entry : m_entries)
        {
            if (!m_bounds.Contains(entry->Position()))
                reinsert.insert(entry);
        }

        if (reinsert.size() > 0)
        {
            for (auto& entry : reinsert)
            {
                m_entries.erase(entry);
                m_root->Insert(entry);
            }
        }
    }
}

void QuadTreeNode::Subdivide()
{
    const float x = m_bounds.x;
    const float y = m_bounds.y;
    const float w = m_bounds.width / 2;
    const float h = m_bounds.height / 2;
    const int depth = m_depth - 1;

    m_branches.insert(new QuadTreeNode(depth, m_capacity, Rectangle(x,      y,      w, h), m_root));
    m_branches.insert(new QuadTreeNode(depth, m_capacity, Rectangle(x + w,  y,      w, h), m_root));
    m_branches.insert(new QuadTreeNode(depth, m_capacity, Rectangle(x,      y + h,  w, h), m_root));
    m_branches.insert(new QuadTreeNode(depth, m_capacity, Rectangle(x + w,  y + h,  w, h), m_root));
}
