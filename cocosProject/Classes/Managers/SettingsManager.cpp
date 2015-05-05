#include "Managers/SettingsManager.h"
#include "Managers/DataManager.h"
#include "Managers/SoundsManager.h"
#include "Managers/DataManager.h"


using namespace cocos2d;

SettingsManager* SettingsManager::getInstance() {
    static SettingsManager instance;
    return &instance;
}

LanguageType SettingsManager::getLanguage() {
    return (LanguageType) DataManager::getInstance()->get(
	"language", 
	(int)Application::getInstance()->getCurrentLanguage()
    );
    }

bool SettingsManager::getIsMusicOn() {
    return DataManager::getInstance()->get("isMusicOn", true);
}

void SettingsManager::setIsMusicOn(bool on) {
    DataManager::getInstance()->put("isMusicOn", on);
    SoundsManager::getInstance()->onMusicSettingsChange(on);
}

bool SettingsManager::getIsSoundEffectsOn() {
    return DataManager::getInstance()->get("isEffects", true);
}

void SettingsManager::setIsSoundEffectsOn(bool on) {
    DataManager::getInstance()->put("isEffects", on);
}

bool SettingsManager::getIsTutorial() {
    return DataManager::getInstance()->get("isTutorial", true);
}

void SettingsManager::setIsTutorial(bool on) {
    DataManager::getInstance()->put("isTutorial", on);
}


Size SettingsManager::getWinSize() {
    auto size = Director::getInstance()->getOpenGLView()->getVisibleSize();
    //size.height -= AdvertisingManager::getInstance()->getBottomAdHeight();
    return size;
}