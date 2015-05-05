#pragma once 

#include "BasicScene.h"
#include <cocos2d.h>
#include "GameElements/TextAsset.h"
#include "GameElements/GapAsset.h"
#include "GameElements/HeroAsset.h"
#include "GameElements/BubbleAsset.h"
#include "Models/LevelModel.h"
#include "Models/Article.h"
#include "Models/GameModel.h"
#include "GUI/LivesAsset.h"


class MainScene : public BasicScene {
public:
    static MainScene* create(const Models::Level*);
    ~MainScene();
private:

    /* STATE */
    const Models::Level* _levelModel;
    Models::GameModel _gameModel;
    bool _gameIsEnding = false;
    
    void gotoReview();
    void gotoMistake(int i);

    /* ELEMENTS */
    cocos2d::Node* _buttonA;
    cocos2d::Node* _buttonAn;
    cocos2d::Node* _buttonThe;
    cocos2d::Node* _buttonEmpty;
    cocos2d::Node* _buttonNextMistake;
    TextAsset* _textAsset;
    GapAsset* _currentGap;
    HeroAsset* _heroAsset;
    LivesAsset* _livesAsset;
    BubbleAsset* _bubbleAsset = nullptr;
    
    /* HANDLERS */
    void onAnswer(Models::Article answer);
    void onNextLine();
    void onLastGap();
    void onLastWord();
    void onGameOver();
    void onCurrentGapMistake(Models::Article answer);
    void onHeroNextWord();
    void onHeroFinishedJump();

    /* INITS */
    bool init(const Models::Level*);
    void initBack();
    void initText();
    void initHero();
    void initButtons();
    void initLives();
    void initTextOver();
    
    /* UPDATES */
    void update(float dt) override;
    void updateHero(float dt);
    
    /* TOOLS */
    cocos2d::Vec2 getPosForHero(float x);
    int getNextTokenColNum() const;
    int getNextTokenLineNum() const ;
    
};










