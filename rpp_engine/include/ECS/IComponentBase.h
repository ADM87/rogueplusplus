#pragma once

#include <string>

namespace rpp
{
    class IComponentBase
    {
    public:

        IComponentBase()                                    = default;
        IComponentBase(const IComponentBase& _component)    = default;

        virtual void Update()                           = 0;
        virtual const std::string& GetTypeId() const    = 0;

        bool Enabled()              { return m_enabled; }
        void Enabled(bool _enabled) { m_enabled = _enabled; }

    private:

        bool m_enabled = true;
    };
}
