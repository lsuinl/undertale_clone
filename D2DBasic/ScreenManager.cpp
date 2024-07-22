#include "ScreenManager.h"

ScreenManager* ScreenManager::pInstanc = nullptr;
ScreenManager::ScreenManager()
{
    if (pInstanc == nullptr) {
        pInstanc = this;
    }
}

ScreenManager::~ScreenManager()
{
}
