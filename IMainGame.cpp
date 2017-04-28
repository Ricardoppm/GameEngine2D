//
//  IMainGame.cpp
//  NinjaPlatformer
//
//  Created by Ricardo Martins on 21/04/2017.
//  Copyright © 2017 Ricardo Martins. All rights reserved.
//

#include "IMainGame.hpp"

#include <memory>

#include "ScreenList.hpp"
#include "IGameScreen.hpp"
#include "Timing.hpp"

namespace Bengine {
    
    IMainGame::IMainGame()
    {
        screenList_ = std::make_unique<ScreenList>(this);
    }
    
    IMainGame::~IMainGame()
    {
        // Empty
    }
    
    void IMainGame::run()
    {
        if( !init())
            return;
        
        FpsLimiter limiter;
        limiter.setTargetFPS(60.f);
        
        isRunning_ = true;
        while (isRunning_)
        {
            limiter.begin();
            
            // Call the custom update and draw methods
            inputManager_.update();
            update();
            if( isRunning_){
                draw();
            
                fps_ = limiter.end();
                window_->swapBuffer();
            }
        }
    }
    
    void IMainGame::exitGame()
    {
        if(screenList_){
            screenList_->destroy();
            screenList_.reset();
        }
        isRunning_ = false;
    }
    
    void IMainGame::onSDLEvent(SDL_Event &event)
    {
        switch (event.type) {
            case SDL_QUIT:
                exitGame();
                break;
            case SDL_MOUSEMOTION:
                inputManager_.setMouseCoords((float)event.motion.x, (float)event.motion.y);
                break;
            case SDL_KEYDOWN:
                inputManager_.pressKey(event.key.keysym.sym);
                break;
            case SDL_KEYUP:
                inputManager_.releaseKey(event.key.keysym.sym);
                break;
            case SDL_MOUSEBUTTONDOWN:
                inputManager_.pressKey(event.button.button);
                break;
            case SDL_MOUSEBUTTONUP:
                inputManager_.releaseKey(event.button.button);
                break;
        }
    }
    
    bool IMainGame::init()
    {
    Bengine::init();
        
        SDL_GL_SetAttribute(SDL_GL_ACCELERATED_VISUAL, 1);
        
        if(!initSystems())
            return false;
        
        onInit();
        
        addScreens();
        
        currentGameScreen_ = screenList_->getCurrent();
        currentGameScreen_->onEntry();
        currentGameScreen_->setRunning();
    
        return true;
    }
    
    bool IMainGame::initSystems()
    {
        // TODO IMPROVE WINDOW CREATE
        window_ = std::make_unique<Window>();
        window_->create("Default", 1080, 700, 0);
        return true;
    }
    
    void IMainGame::update()
    {
        if( currentGameScreen_){
            switch (currentGameScreen_->getScreenState()) {
                case ScreenState::RUNNING:
                    currentGameScreen_->update();
                    break;
                
                case ScreenState::CHANGE_NEXT:
                    currentGameScreen_->onExit();
                    currentGameScreen_ = screenList_->moveNext();
                    if( currentGameScreen_){
                        currentGameScreen_->setRunning();
                        currentGameScreen_->onEntry();
                    }
                    break;
                    
                case ScreenState::CHANGE_PREVIOUS:
                    currentGameScreen_->onExit();
                    currentGameScreen_ = screenList_->movePrevious();
                    if( currentGameScreen_){
                        currentGameScreen_->setRunning();
                        currentGameScreen_->onEntry();
                    }
                    break;
                    
                case ScreenState::EXIT_APPLICATION:
                    exitGame();
                    break;
                    
                default:
                    break;
            }
        }
        else{
            exitGame();
        }
    }
    
    void IMainGame::draw()
    {
        glViewport(0, 0, window_->getScreenWidth(), window_->getScreenHeight());
        if(currentGameScreen_ && currentGameScreen_->getScreenState() == ScreenState::RUNNING){
            currentGameScreen_->draw();
        }
            
    }
    
}
