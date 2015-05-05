#include "TextAsset.h"
#include "GUI/GUI.h"
#include "Utils.h"
#include "GapAsset.h"

#include <string>

using namespace cocos2d;
using namespace Models;
using namespace std;

bool TextAsset::init() {
    if(!Node::init())
        return false;
    setContentSize(Director::getInstance()->getVisibleSize());
    return true;
}

void TextAsset::setModel(const Models::Level* model) {
    _model = model;
    TOP_OFFSET = 30;
    ROW_HEIGHT = Director::getInstance()->getVisibleSize().height * 0.08;
    initLines();
}

GapAsset* TextAsset::getGapAt(int i) {
    return _gaps.at(i);
}

void TextAsset::initLines() {
    _linesNode = Node::create();
    _linesNode->setContentSize(getContentSize());
    
    addChild(_linesNode);
    _linesNode->setPosition({0, -TOP_OFFSET});
    for(auto row: _model->rows) {
        addLine(row);
    }
}

void TextAsset::scrollToLine(int i) {
    // TODO: move _linesNode
    // use fixed time move animation
    float offset = -ROW_HEIGHT * i + TOP_OFFSET;
    _linesNode->runAction(MoveTo::create(1, Vec2(0, -offset)));
}


struct RowAsset : Node {
    CREATE_FUNC(RowAsset);
    bool init() {
        if(!Node::init()) return false;
        return true;
    }
    
    void setModel(const LevelRow& row) {
        for(auto t: row.tokens) {
            addToken(t);
        }
    }
    
    void addToken(const string& str) {
        if(str == "???") {
            auto gap = GapAsset::create();
            addChild(gap);
            gap->setPosition({prevOffset + 20, 5});
            _textAsset->_offsets.back().push_back(prevOffset + 25);
            _textAsset->_gapsFlags.back().push_back(true);
            prevOffset += 50;
            _textAsset->_gaps.push_back(gap);
            
        } else {
            auto label = GUI::createLabelR(str, 18);
            label->setAnchorPoint({0,1});
            label->setPosition({prevOffset, 0});
            label->setColor(Color3B::BLACK);
            addChild(label);
            _textAsset->_offsets.back().push_back(prevOffset + label->getContentSize().width/2);
            _textAsset->_gapsFlags.back().push_back(false);
            prevOffset+=label->getContentSize().width + 10;
        }
    }
    float prevOffset = 0;
    TextAsset* _textAsset;
    
};


void TextAsset::addLine(const LevelRow& levelRow) {
    _currentLineNumber++;
    _offsets.push_back(vector<float>());
    _gapsFlags.push_back(vector<bool>());
    auto row = RowAsset::create();
    row->_textAsset = this;
    row->setModel(levelRow);
    Vec2 pos(Director::getInstance()->getWinSize());
    pos.x *= 0.05;
    pos.y -= ROW_HEIGHT * _currentLineNumber;
    row->setPosition(pos);
    _linesNode->addChild(row, 1);
}











