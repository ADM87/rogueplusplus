#include <Game/GameObject.h>
#include <Structures/QuadTree.h>

#include <algorithm>
#include <cassert>

using namespace rpp;

#pragma region TreeUtility

bool InsertOnBranch(QuadTreeNode* _branch, GameObject* _gameObject)
{
    if (_branch == nullptr)
        return false;

    return _branch->Insert(_gameObject);
}

bool ReinsertOnBranch(QuadTreeNode* _branch, GameObject* _gameObject)
{
    if (_branch == nullptr)
        return false;

    return _branch->Reinsert(_gameObject);
}

bool RemoveFromBranch(QuadTreeNode* _branch, GameObject* _gameObject)
{
    if (_branch == nullptr)
        return false;

    return _branch->Erase(_gameObject);
}

bool ExistsOnBranch(QuadTreeNode* _branch, GameObject* _gameObject)
{
    if (_branch == nullptr)
        return false;

    return _branch->Has(_gameObject);
}

void UpdateBranch(QuadTreeNode* _branch)
{
    if (_branch == nullptr)
        return;

    _branch->Update();
}

void DistributeToBranch(QuadTreeNode* _branch, std::unordered_set<GameObject*>& _gameObjects)
{
    if (_branch == nullptr || _gameObjects.size() == 0)
        return;

    std::unordered_set<GameObject*> container(_gameObjects);

    for (auto& go : container)
    {
        if (_branch->Insert(go))
            _gameObjects.erase(go);
    }
}

void QueryBranch(QuadTreeNode* _branch, const Rectangle& _region, std::unordered_set<GameObject*>& _result)
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
    // Don't delete the parent node!
    m_parent = nullptr;

    for (auto& branch : m_branches)
        PruneBranch(branch);

    m_branches.clear();
    m_gameObjects.clear();
}

bool QuadTreeNode::Insert(GameObject* _gameObject)
{
    if (_gameObject == nullptr || !m_bounds.Contains(_gameObject->Transform()->Position()))
        return false;

    // If depth is 0, the node cannot be subdivided so allow it to overflow.
    if (m_depth == 0 || (!m_branches.size() && m_gameObjects.size() < m_capacity))
    {
        m_gameObjects.insert(_gameObject);
        return true;
    }

    if (!m_branches.size())
    {
        Subdivide();
        for (auto& branch : m_branches)
            DistributeToBranch(branch, m_gameObjects);

        assert(!m_gameObjects.size() && "Failed to distribute quad tree entries to child branches");
    }

    for (auto& branch : m_branches)
    {
        if (InsertOnBranch(branch, _gameObject))
            return true;
    }

    return false;
}

bool QuadTreeNode::Reinsert(GameObject* _gameObject)
{
    if (m_parent == nullptr || _gameObject == nullptr)
        return false;

    if (!m_parent->Insert(_gameObject))
        return m_parent->Reinsert(_gameObject);

    return true;
}

bool QuadTreeNode::Erase(GameObject* _gameObject)
{
    if (m_branches.size())
    {
        for (auto& branch : m_branches)
        {
            if (RemoveFromBranch(branch, _gameObject))
                return true;
        }

        return false;
    }

    if (m_gameObjects.size())
    {
        auto it = std::find(m_gameObjects.begin(), m_gameObjects.end(), _gameObject);
        if (it != m_gameObjects.end())
        {
            m_gameObjects.erase(it);
            return true;
        }
    }

    return false;
}

bool QuadTreeNode::Has(GameObject* _gameObject)
{
    if (m_branches.size())
    {
        for (auto& branch : m_branches)
        {
            if (ExistsOnBranch(branch, _gameObject))
                return true;
        }

        return false;
    }

    if (m_gameObjects.size())
        return std::find(m_gameObjects.begin(), m_gameObjects.end(), _gameObject) != m_gameObjects.end();

    return false;
}

void QuadTreeNode::Query(const Rectangle& _region, std::unordered_set<GameObject*>& _result)
{
    if (!_region.Overlaps(m_bounds))
        return;

    if (m_branches.size())
    {
        for (auto& it : m_branches)
            QueryBranch(it, _region, _result);

        return;
    }

    if (m_gameObjects.size())
    {
        for (auto& go : m_gameObjects)
        {
            if (_region.Contains(go->Transform()->Position()))
                _result.insert(go);
        }
    }
}

void QuadTreeNode::Refresh()
{
    Refresh(m_bounds);
}

void QuadTreeNode::Refresh(const Rectangle& _region)
{
    if (!_region.Overlaps(m_bounds))
        return;

    if (m_branches.size())
    {
        for (auto& branch : m_branches)
            RefreshBranch(branch, _region);

        std::unordered_set<GameObject*> container;
        Query(m_bounds, container);

        if (container.size() <= m_capacity)
        {
            if (container.size())
                m_gameObjects.insert(container.begin(), container.end());

            for (auto& branch : m_branches)
                PruneBranch(branch);

            m_branches.clear();
        }

        return;
    }

    if (m_gameObjects.size())
    {
        std::unordered_set<GameObject*> reinsert;

        for (auto& go : m_gameObjects)
        {
            if (!m_bounds.Contains(go->Transform()->Position()))
                reinsert.insert(go);
        }

        if (reinsert.size())
        {
            for (auto& go : reinsert)
            {
                if (m_parent->Reinsert(go))
                    m_gameObjects.erase(go);
            }

            assert(reinsert.size() && ("Failed to reinsert some gameobjects into parent nodes"));
        }
    }
}

void QuadTreeNode::Update()
{
    if (m_branches.size())
    {
        for (auto& branch : m_branches)
            branch->Update();

        return;
    }

    if (m_gameObjects.size())
    {
        for (auto& go : m_gameObjects)
            go->Update();
    }
}

void QuadTreeNode::Subdivide()
{
    const float x = m_bounds.x;
    const float y = m_bounds.y;
    const float w = m_bounds.width / 2;
    const float h = m_bounds.height / 2;
    const int depth = m_depth - 1;

    m_branches.insert(new QuadTreeNode(depth, m_capacity, Rectangle(x,      y,      w, h), this));
    m_branches.insert(new QuadTreeNode(depth, m_capacity, Rectangle(x + w,  y,      w, h), this));
    m_branches.insert(new QuadTreeNode(depth, m_capacity, Rectangle(x,      y + h,  w, h), this));
    m_branches.insert(new QuadTreeNode(depth, m_capacity, Rectangle(x + w,  y + h,  w, h), this));
}
