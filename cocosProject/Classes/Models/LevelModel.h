#pragma once


#include <vector>
#include <string>
#include "Utils.h"
#include "Article.h"

namespace Models {

    struct LevelRow {
        std::vector<std::string> tokens;
    };
    
    struct Answer {
        Article article;
        std::string description;
        int line;
        int col;
    };

    struct Level {
        std::vector<Answer> answers;
        std::vector<LevelRow> rows;
        int num;
    };

}