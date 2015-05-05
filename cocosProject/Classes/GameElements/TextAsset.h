#pragma once

#include <cocos2d.h>
#include "Models/LevelModel.h"
#include "GapAsset.h"
#include <vector>

class TextAsset : public cocos2d::Node {

public:
    CREATE_FUNC(TextAsset);
    void setModel(const Models::Level* model);
    GapAsset* getGapAt(int i);
    void scrollToLine(int line);
    
    std::vector<GapAsset*> _gaps;
    std::vector<std::vector<float>> _offsets;
    std::vector<std::vector<bool>> _gapsFlags;
    
    
private:
    
    /* CONSTANTS */
    float ROW_HEIGHT = 0;
    float TOP_OFFSET = 0;

    /* STATE */
    const Models::Level* _model;
    float _currentLineNumber = 0;
    
    
    /* ELEMENTS */
    cocos2d::Node* _linesNode;
    
    /* INITS */
    bool init() override;
    void initLines();
    
    /* FUNS */
    void addLine(const Models::LevelRow& levelRow);
    
};