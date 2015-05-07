#include <vector>

#include "Managers/BasicManager.h"
#include "Managers/ScenesManager.h"
#include "Managers/DataManager.h"

#include "AppDelegate.h"


using namespace cocos2d;
using namespace std;


/* INITS */

bool AppDelegate::init() {
    auto director = Director::getInstance();
    auto glview = director->getOpenGLView();
    if (!glview) {
	glview = GLViewImpl::createWithRect("Foxy Bird", Rect(100, 100,
	    1280, 640
	));
        director->setOpenGLView(glview);
    }
    multiresolutionSupport();
#ifdef COCOS2D_DEBUG
    //director->setDisplayStats(true);
    //TODO: add choose resource folder
#endif
    director->setAnimationInterval(1.0 / 60);
    ScenesManager::getInstance()->runWithGame();
    //ScenesManager::getInstance()->runWithSpring();
    return true;
}

bool AppDelegate::initManagers() {
    auto p = [this](BasicManager* bm){ _managers.push_back(bm); };
    p(DataManager::getInstance());
    p(ScenesManager::getInstance());
    bool ok = true;
    forAllManagers([&ok](BasicManager* m) {
	if(!m->init())
	    ok = false;
    });
    if(!ok) return false;
    return true;
}

/* HANDLERS */

void AppDelegate::applicationDidEnterBackground() {
    forAllManagers([](BasicManager* m) { 
	m->onAppPause();
    });
    Director::getInstance()->stopAnimation();
    Director::getInstance()->pause();
}

void AppDelegate::applicationWillEnterForeground() {
    Director::getInstance()->startAnimation();
    Director::getInstance()->resume();
    forAllManagers([](BasicManager* m) { 
	m->onAppResume();
    });
}

/* FUNS */

void AppDelegate::multiresolutionSupport() {
    auto director = Director::getInstance();
    auto glview = director->getOpenGLView();
    Size designSize = cocos2d::Size(640, 320);
    Size resourceSize = cocos2d::Size(640, 320);
    Size screenSize = glview->getFrameSize();
    designSize = Size(screenSize.width / 2, screenSize.height / 2);
    resourceSize = screenSize;
    director->setContentScaleFactor(resourceSize.width / designSize.width);
    glview->setDesignResolutionSize(640, 320, ResolutionPolicy::FIXED_WIDTH);
    
//    if (screenSize.width < 480) {
//	// it is HD. we decided not to support SD
//	FileUtils::getInstance()->addSearchResolutionsOrder("HD");
//    } else if (480 <= screenSize.width && screenSize.width < 1152) {
//	FileUtils::getInstance()->addSearchResolutionsOrder("HD");
//    } else {
//	FileUtils::getInstance()->addSearchResolutionsOrder("HDR");
//    }
}

/* TOOLS */

void AppDelegate::forAllManagers(function<void(BasicManager*)> f) {
    for(size_t t = 0; t < _managers.size(); t++) {
	BasicManager* m = _managers.at(t);
	f(m);
    }
}
