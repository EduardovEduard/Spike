#pragma once

#include <string>
#include <vector>

namespace Models {
    enum class HeroJumpState {
	idle,
	inFirstJump,
	inSecondJump
    };
    struct GameModel {
        float heroWaitTime = 0;
        HeroJumpState heroJumpState = HeroJumpState::idle;
        bool gameComplete = false;
    };
}