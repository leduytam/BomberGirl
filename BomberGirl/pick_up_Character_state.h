#pragma once
#include"base_state.h"

namespace Bombergirl{
	class PickUpCharacterState :public BaseState
	{
    private:
    public:
        PickUpCharacterState(SharedContext* sharedContext);

        void init() override;
        void handleInput() override;
        void update(const float&) override;
        void render() override;
	};
}


