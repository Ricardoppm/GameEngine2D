//
//  ScreenList.cpp
//  NinjaPlatformer
//
//  Created by Ricardo Martins on 21/04/2017.
//  Copyright © 2017 Ricardo Martins. All rights reserved.
//

#include "ScreenList.hpp"

#include "IGameScreen.hpp"

namespace Bengine {
    ScreenList::ScreenList(IMainGame* game):
    game_(game)
    {
        // empty
    }
    
    ScreenList::~ScreenList()
    {
        destroy();
    }
    
    IGameScreen* ScreenList::moveNext()
    {
        IGameScreen* currentScreen = getCurrent();
        if( currentScreen->getNextScreenIndex() != SCREEN_INDEX_NO_SCREEN){
            currentScreenIndex_ = currentScreen->getNextScreenIndex();
        }
        return getCurrent();
    }
    
    IGameScreen* ScreenList::movePrevious()
    {
        IGameScreen* currentScreen = getCurrent();
        if( currentScreen->getPreviousScreenIndex() != SCREEN_INDEX_NO_SCREEN){
            currentScreenIndex_ = currentScreen->getPreviousScreenIndex();
        }
        return getCurrent();
    }
    
    void ScreenList::setScreen(int nextScreen){ currentScreenIndex_ = nextScreen; }
    
    void ScreenList::addScreen(Bengine::IGameScreen* newScreen)
    {
        screens_.push_back(newScreen);
        newScreen->build();
        newScreen->setParentGame(game_);
        newScreen->screenIndex_ = screens_.size()-1;
    }
    
    void ScreenList::destroy()
    {
        for (size_t i = 0; i < screens_.size(); i++) {
            screens_[i]->destroy();
        }
        screens_.resize(0);
        currentScreenIndex_ = SCREEN_INDEX_NO_SCREEN;
    }
    
    IGameScreen* ScreenList::getCurrent() const
    {
        if( currentScreenIndex_ == SCREEN_INDEX_NO_SCREEN)
            return nullptr;
        return screens_[currentScreenIndex_];
    }

}
