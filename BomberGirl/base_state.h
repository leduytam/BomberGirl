#pragma once

#include "shared_context.h"

namespace bombergirl
{
    class BaseState
    {
    protected:
        SharedContext* m_sharedContext;
        bool m_isTransparent;
    public:
        BaseState(SharedContext*);

        virtual void init() = 0;
        virtual void handleInput() = 0;
        virtual void update(const float&) = 0;
        virtual void render() = 0;

        bool isTransparent() const;
        void setTransparent(const bool&);
    };
}

