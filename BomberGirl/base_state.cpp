#include "base_state.h"
#include "shared_context.h"

Bombergirl::BaseState::BaseState(SharedContext* sharedContext) : m_sharedContext(sharedContext), m_isTransparent(false) {}

bool Bombergirl::BaseState::isTransparent() const
{
    return m_isTransparent;
}

void Bombergirl::BaseState::setTransparent(const bool& isTransparent)
{
    m_isTransparent = isTransparent;
}
Bombergirl::SharedContext* Bombergirl::BaseState::getSharedContext() const
{
    return m_sharedContext;
}
