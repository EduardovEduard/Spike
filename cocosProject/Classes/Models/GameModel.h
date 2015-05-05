#pragma once

#include <string>
#include <vector>

namespace Models {
    struct GameModel {
        int currentLine = 0;
        int currentToken = 0;
        int currentGapNum = 0;
        int textFieldLine = 0;
        float heroCurrentWaitTime = 0;
        float heroJumpTime;
        float heroWaitTime = 0;
        bool heroInJump = false;
        int lives = 5;
        bool gameComplete = false;
        std::vector<int> mistakes;
        int currentMistake = 0;
    };
}