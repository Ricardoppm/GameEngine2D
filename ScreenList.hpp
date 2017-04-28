//
//  ScreenList.hpp
//  NinjaPlatformer
//
//  Created by Ricardo Martins on 21/04/2017.
//  Copyright © 2017 Ricardo Martins. All rights reserved.
//

#ifndef ScreenList_hpp
#define ScreenList_hpp

#include <vector>

namespace Bengine {
    
    class IMainGame;
    class IGameScreen;
    
    class ScreenList
    {
    public:
        ScreenList(IMainGame* game);
        ~ScreenList();
        
        IGameScreen* moveNext();
        IGameScreen* movePrevious();
        
        void setScreen(int nextScreen);
        void addScreen(IGameScreen* newScreen);
        
        void destroy();
        
        // Getters
        IGameScreen* getCurrent() const;

    protected:
        IMainGame* game_ = nullptr;
        std::vector<IGameScreen*> screens_;
        int currentScreenIndex_ = -1;
    };
}
#endif /* ScreenList_hpp */
