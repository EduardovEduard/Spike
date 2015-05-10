#pragma once

#include <cocos2d.h>

#include <sstream>
#include <string>

#define CREATE_FUNCTION \
template <class... Args> \
static auto create(Args&&... args) -> decltype(this) \
{ \
    auto pRet = new typename std::remove_pointer<decltype(create(args...))>::type; \
    if (pRet && pRet->init(std::forward<Args>(args)...)) \
    { \
        pRet->autorelease(); \
        return pRet; \
    } \
    else \
    { \
        delete pRet; \
        pRet = NULL; \
        return NULL; \
    } \
} \

namespace Utils {

    template<class T>
    inline std::string toString(T obj) {
	std::stringstream str;
	str << obj;
	return str.str();
    }
    
    void drawRect(
	cocos2d::DrawNode* node, 
	const cocos2d::Rect& rect,
	const cocos2d::Color4F &fillColor,
	float borderWidth = 0,
	const cocos2d::Color4F &borderColor = cocos2d::Color4F::BLACK
    );
    
    void  setNodeWidth(cocos2d::Node* node, float width);
    float setNodeWidthR(cocos2d::Node* node, float relativeWidth);
    void  setNodeHeight(cocos2d::Node* node, float height);
    float setNodeHeightR(cocos2d::Node* node, float relativeHeight);
    
    // relative to parent in percent
    void setPosition(cocos2d::Node* node, float x, float y);
    inline void setPosition(cocos2d::Node* node, cocos2d::Vec2 pos) {
	setPosition(node, pos.x, pos.y);
    }
    inline void setPosition(cocos2d::Node* node, float v) {
	setPosition(node, v, v);
    }
    
    std::string getFileData(const std::string& path);
    
    float getFontSize(float fs);
    
    unsigned long getTimeTick();
    
    void exit();
        
    cocos2d::Color3B colorFromString(const std::string& str);
    
    inline cocos2d::Vec2 coordFromPSD(cocos2d::Vec2 pos) {
	auto _size = cocos2d::Director::getInstance()->getVisibleSize();
	if(pos.x < 0) pos.x += 854;
	if(pos.y < 0) pos.y += 480;
	return cocos2d::Vec2(
	    _size.width  * pos.x/854,
	    _size.height * (1 - pos.y/480)
	);
    };
    
    inline void setPosPsd(cocos2d::Node* node, float x, float y) {
        auto pos = coordFromPSD(cocos2d::Vec2(x,y));
        node->setPosition(pos);
    }
}






