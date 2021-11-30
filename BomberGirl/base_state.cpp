#include "base_state.h"
#include "shared_context.h"

bombergirl::BaseState::BaseState(SharedContext* sharedContext) : m_sharedContext(sharedContext), m_isTransparent(false) {}

bool bombergirl::BaseState::isTransparent() const
{
    return m_isTransparent;
}

void bombergirl::BaseState::setTransparent(const bool& isTransparent)
{
    m_isTransparent = isTransparent;
}