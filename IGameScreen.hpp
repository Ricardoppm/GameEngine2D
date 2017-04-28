//
//  IGameScreen.hpp
//  NinjaPlatformer
//
//  Created by Ricardo Martins on 21/04/2017.
//  Copyright © 2017 Ricardo Martins. All rights reserved.
//

#ifndef IGameScreen_hpp
#define IGameScreen_hpp

#define SCREEN_INDEX_NO_SCREEN -1

namespace Bengine {
    
    class IMainGame;
    
    enum class ScreenState{
        NONE,
        RUNNING,
        EXIT_APPLICATION,
        CHANGE_NEXT,
        CHANGE_PREVIOUS
    };
    
    class IGameScreen
    {
    public:
        friend class ScreenList;
        
        IGameScreen(){
            // Empty
        }
        // When making base classes, make destructor virtual
        virtual ~IGameScreen(){
            // Empty
        }
        
        // Returns the index of the previous/next screen
        virtual int getNextScreenIndex() const = 0;
        virtual int getPreviousScreenIndex() const = 0;
        
        // Called at beginning and end of the application
        virtual void build() = 0;
        virtual void destroy() = 0;
        
        // Called when screen enters/exits focus
        virtual void onEntry() = 0;
        virtual void onExit() = 0;
        
        // Called in the main game loop
        virtual void update() = 0;
        virtual void draw() = 0;
        
        // Getters
        int getIndex() const { return screenIndex_; }
        ScreenState getScreenState() const { return currentState_; }
        
        // Setters
        void setParentGame(IMainGame* game) { game_ = game; }
        void setRunning() { currentState_ = ScreenState::RUNNING; }
        
        
        
    protected:
        ScreenState currentState_ = ScreenState::NONE;
        IMainGame* game_ = nullptr;
        
        int screenIndex_ = -1;
        
    };
}
#endif /* IGameScreen_hpp */
