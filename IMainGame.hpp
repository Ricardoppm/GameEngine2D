//
//  IMainGame.hpp
//  NinjaPlatformer
//
//  Created by Ricardo Martins on 21/04/2017.
//  Copyright © 2017 Ricardo Martins. All rights reserved.
//

#ifndef IMainGame_hpp
#define IMainGame_hpp

#include <memory>

#include "Bengine.hpp"
#include "Window.hpp"
#include "InputManager.hpp"

namespace Bengine {

    class ScreenList;
    class IGameScreen;
    
    class IMainGame
    {
    public:
        IMainGame();
        // When making base classes, make destructor virtual
        virtual ~IMainGame();
        
        void run();
        void exitGame();
        
        // Called on initialization
        virtual void onInit() = 0;
        //For adding all screen
        virtual void addScreens() = 0;
        // Called when exiting
        virtual void onExit() = 0;
        
        
        void onSDLEvent(SDL_Event& event);

        // Getters
        const float getFPS() const { return fps_; }
        InputManager& getInputManager() { return inputManager_; }
    protected:
        // CUstom Update funtion
        virtual void update();
        // Custom draw functions
        virtual void draw();
        
        
        bool init();
        bool initSystems();
        
        
        std::unique_ptr<ScreenList> screenList_;
        IGameScreen* currentGameScreen_ = nullptr;
        bool isRunning_ = false;
        float fps_ = 0.f;
        std::unique_ptr<Window> window_;
        InputManager inputManager_;
    };
}
#endif /* IMainGame_hpp */
