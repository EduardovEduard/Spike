#include "MainScene.h"
#include "Managers/ScenesManager.h"
#include "Managers/SoundsManager.h"
#include "Managers/LevelsManager.h"
#include "Models/LevelModel.h"
#include "Utils.h"
#include "GUI/GUI.h"
#include "GUI/GameOverLayer.h"
#include "GUI/ResultsLayer.h"

#include <iostream>


using namespace cocos2d;
using namespace GUI;
using namespace Models;
using namespace std;

MainScene* MainScene::create(const Models::Level* lvl) 
{ 
    auto *pRet = new MainScene();
    if (pRet && pRet->init(lvl))
    {
        pRet->autorelease();
        return pRet; 
    } else { 
        delete pRet; 
        pRet = NULL; 
        return NULL; 
    } 
}

bool MainScene::init(const Models::Level* lvl) {
    if(!BasicScene::init()) return false;
    _levelModel = lvl;
    initBack();
    initText();
    initTextOver();
    initHero();
    initLives();
    initButtons();
    scheduleUpdate();
    return true;
}

void MainScene::initBack() {
    auto l = LayerColor::create(Color4B::WHITE);
    addChild(l, 1);
}


void MainScene::initText() {
    _textAsset = TextAsset::create();
    _textAsset->setModel(_levelModel);
    _textAsset->setPosition({0,0});
    addChild(_textAsset, 2);
}

void MainScene::initHero() {
    _heroAsset = HeroAsset::create();
    _heroAsset->setPosition(Vec2(100.0,_size.height * 0.95));
    _heroAsset->setPosition(getPosForHero(_textAsset->_offsets.at(0).at(0)));
    _gameModel.heroWaitTime = 0.1;
    _gameModel.heroJumpTime = 0.9;
    addChild(_heroAsset, 5);
}

void MainScene::initTextOver() {
    auto l = LayerColor::create(Color4B(255,255,255,240), _size.width, _size.height * 0.4);
    l->setAnchorPoint({0,0});
    l->setPosition({0,0});
    addChild(l,3);
    
    l = LayerColor::create(Color4B(255,255,255,240), _size.width, _size.height * 0.2);
    l->setAnchorPoint({0,1});
    l->setPosition({0,_size.height*0.85f});
    addChild(l,3);
}

void MainScene::initButtons() {
    
    const Size BUTTON_SIZE(_size.width / 3, _size.height / 7);
    
    _buttonA = TextButton::create(
        BUTTON_SIZE, "A", [this](){ onAnswer(Article::A); }, Color3B::BLACK, Color3B::BLACK, Color3B::BLACK, Color3B::WHITE
    );
    _buttonAn = TextButton::create(
        BUTTON_SIZE, "An", [this](){ onAnswer(Article::AN); }, Color3B::BLACK, Color3B::BLACK, Color3B::BLACK, Color3B::WHITE
    );
    _buttonThe = TextButton::create(
        BUTTON_SIZE, "The", [this](){ onAnswer(Article::THE); }, Color3B::BLACK, Color3B::BLACK, Color3B::BLACK, Color3B::WHITE
    );
    _buttonEmpty = TextButton::create(
        BUTTON_SIZE, "_", [this](){ onAnswer(Article::EMPTY); }, Color3B::BLACK, Color3B::BLACK, Color3B::BLACK, Color3B::WHITE
    );
    _buttonA->setAnchorPoint({0,0.5}); _buttonAn->setAnchorPoint({0,0.5});
    _buttonThe->setAnchorPoint({1,0.5}); _buttonEmpty->setAnchorPoint({1,0.5});
    
    addChild(_buttonA, 4);
    addChild(_buttonAn, 4);
    addChild(_buttonThe, 4);
    addChild(_buttonEmpty, 4);
    
    Utils::setPosition(_buttonA, 0.1, 0.1);
    Utils::setPosition(_buttonAn, 0.1, 0.3);
    Utils::setPosition(_buttonThe, 0.9, 0.1);
    Utils::setPosition(_buttonEmpty, 0.9, 0.3);
    
}

void MainScene::initLives() {
    _livesAsset = LivesAsset::create();
    _livesAsset->setPosition(_size.width * 0.75f, _size.height * 0.94);
    addChild(_livesAsset, 7);
}

/* STATE */

void MainScene::gotoReview() {

    unscheduleUpdate();
    
    _heroAsset->setVisible(false);
    
    // HIDE
    _buttonA->setVisible(false);
    _buttonAn->setVisible(false);
    _buttonThe->setVisible(false);
    _buttonEmpty->setVisible(false);
    
    // BUBBLE
    _bubbleAsset = BubbleAsset::create();
    addChild(_bubbleAsset, 10);
    gotoMistake(0);
    
    // BUTTON
    const Size BUTTON_SIZE(_size.width / 3, _size.height / 6);
    _buttonNextMistake = TextButton::create(
        BUTTON_SIZE, "Next", [this]() {
            gotoMistake(_gameModel.currentMistake + 1); 
        },
        Color3B::BLACK, Color3B::BLACK, Color3B::BLACK, Color3B::WHITE
    );
    addChild(_buttonNextMistake, 4);
    Utils::setPosition(_buttonNextMistake, 0.5, 0.15);
    
}

void MainScene::gotoMistake(int i) {
    _gameModel.currentMistake = i;
    int gapNum = _gameModel.mistakes.at(i);
    auto answ = _levelModel->answers.at(gapNum);
    _textAsset->scrollToLine(answ.line);
    _bubbleAsset->setText(answ.description);
    float x = _textAsset->_offsets.at(answ.line).at(answ.col);
    _bubbleAsset->setPosition(getPosForHero(x));
    if(_gameModel.currentMistake + 1 == _gameModel.mistakes.size()) {
        _buttonNextMistake->setVisible(false);
        // BUTTON
        const Size BUTTON_SIZE(_size.width / 3, _size.height / 6);
        auto buttonRestart = TextButton::create(
            BUTTON_SIZE, "Restart", [this]() {
                ScenesManager::getInstance()->gotoMain(_levelModel->num);
            },
            Color3B::BLACK, Color3B::BLACK, Color3B::BLACK, Color3B::WHITE
        );
        addChild(buttonRestart, 4);
        Utils::setPosition(buttonRestart, 0.5, 0.15);
    }
}

/* HANDLERS */

void MainScene::onAnswer(Article answer) {
    auto expectedAnswer = _levelModel->answers.at(_gameModel.currentGapNum);
    bool success = expectedAnswer.article == answer;
    if(!success) {
        onCurrentGapMistake(answer);
    } else {
        _textAsset->getGapAt(_gameModel.currentGapNum)->unlock(answer, true);
        _gameModel.currentGapNum++;
        if(_gameModel.currentGapNum == _levelModel->answers.size()) {
            onLastGap();
        }
    }
}

void MainScene::onLastGap() {
    auto getActoin = [](Node* n) {
        auto pos = n->getPosition();
        n->runAction(
            EaseIn::create(MoveTo::create(0.8, Vec2(pos.x, -100)), 2)
        );
    };
    getActoin(_buttonA);
    getActoin(_buttonAn);
    getActoin(_buttonThe);
    getActoin(_buttonEmpty);
    _gameIsEnding = true;
}

void MainScene::onLastWord() {
    _gameModel.gameComplete = true;
    _heroAsset->runAction(EaseIn::create(ScaleTo::create(0.7, 0), 3));\
    _textAsset->scrollToLine(_gameModel.currentLine + 2);
    _livesAsset->setVisible(false);
    runAction(Sequence::create(
        DelayTime::create(1),
        CallFunc::create([this]() {
            auto l = ResultsLayer::create();
            l->setOnRestart([this]() {
                ScenesManager::getInstance()->gotoMain(_levelModel->num);
            });
            l->setOnNext([this]() {
                ScenesManager::getInstance()->gotoMain(_levelModel->num+1);
            });
            addChild(l, 100);
        }), NULL
    ));
}

void MainScene::onCurrentGapMistake(Article answer) {
    _gameModel.mistakes.push_back(_gameModel.currentGapNum);
    _gameModel.lives--;
    if(_gameModel.lives == 0) {
        onGameOver();
        return;
    }
    _livesAsset->removeLife();
    _textAsset->getGapAt(_gameModel.currentGapNum)->unlock(answer, false);
    _gameModel.currentGapNum++;
    if(_gameModel.currentGapNum == _levelModel->answers.size()) {
        onLastGap();
    }
}

void MainScene::onGameOver() {
    unscheduleUpdate();
    _heroAsset->runAction(Sequence::create(
        ScaleTo::create(1, 100),
        CallFunc::create([this]() {
            auto l = GameOverLayer::create();
            l->setOnRestart([this](){
                ScenesManager::getInstance()->gotoMain(_levelModel->num);
            });
            l->setOnReview([this, l]() {
                l->setVisible(false);
                gotoReview();
            });
            addChild(l, 100);
        }), NULL
    ));
}

void MainScene::onHeroNextWord() {
    int nextTokenCol = getNextTokenColNum();
    int nextTokenLine = getNextTokenLineNum();
    if(nextTokenCol == -1) {
        onLastWord();
        return;
    }
    if(_gameIsEnding) {
        _gameModel.heroJumpTime *= 0.8;
    }
    float x = _textAsset->_offsets.at(nextTokenLine).at(nextTokenCol);
    _gameModel.heroInJump = true;
    _heroAsset->runAction(Sequence::create(EaseInOut::create(JumpTo::create(
        _gameModel.heroJumpTime * 0.9, getPosForHero(x), 25, 1
    ), 3), CallFunc::create([this](){ onHeroFinishedJump(); }), nullptr));
}

void MainScene::onHeroFinishedJump() {
    _gameModel.heroInJump = false;
    int prevLineNum = _gameModel.currentLine;
    int nextCol = getNextTokenColNum();
    int nextLine = getNextTokenLineNum();
    _gameModel.currentToken = nextCol;
    _gameModel.currentLine = nextLine;
    
    if(_gameModel.currentLine == -1) {
        return;
    }
    if(_textAsset->_gapsFlags.at(_gameModel.currentLine).at(_gameModel.currentToken)) {
        if(_gameModel.currentGapNum < _levelModel->answers.size()) {
            if(
                _levelModel->answers.at(_gameModel.currentGapNum).line == _gameModel.currentLine &&
                _levelModel->answers.at(_gameModel.currentGapNum).col == _gameModel.currentToken
            ) {
                onCurrentGapMistake(Article::UNKNOWN);
            }
        }
    }
    if(prevLineNum != _gameModel.currentLine) {
        onNextLine();
    }
}

void MainScene::onNextLine() {
    _textAsset->scrollToLine(_gameModel.currentLine);
}

/* UPDATES */

void MainScene::update(float dt) {
    updateHero(dt);
}

void MainScene::updateHero(float dt) {
    if(_gameModel.gameComplete) return; 
    if(_gameModel.heroInJump) return;
    _gameModel.heroCurrentWaitTime += dt;
    if(_gameModel.heroCurrentWaitTime < _gameModel.heroWaitTime) return;
    _gameModel.heroCurrentWaitTime = 0;
    onHeroNextWord();
}

Vec2 MainScene::getPosForHero(float x) {
    return Vec2(x + _size.width * 0.05, _size.height * 0.9);
}

int MainScene::getNextTokenColNum() const {
    if((1 + _gameModel.currentToken) == _levelModel->rows.at(_gameModel.currentLine).tokens.size()) {
        if((1 + _gameModel.currentLine) == _levelModel->rows.size()) 
            return -1;
        return 0;
    }
    return 1 + _gameModel.currentToken;
}

int MainScene::getNextTokenLineNum() const {
    int t = getNextTokenColNum();
    if(t == -1) return -1;
    if(t == 0) return _gameModel.currentLine + 1;
    return _gameModel.currentLine;
}

MainScene::~MainScene() {
    delete _levelModel;
}











