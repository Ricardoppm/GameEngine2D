//
//  GUI.hpp
//  NinjaPlatformer
//
//  Created by Ricardo Martins on 26/04/2017.
//  Copyright © 2017 Ricardo Martins. All rights reserved.
//

#ifndef GUI_hpp
#define GUI_hpp

#include <CEGUI/CEGUI.h>
#include <CEGUI/RendererModules/OpenGL/GL3Renderer.h>

#include <SDL2/SDL_events.h>

#include <glm/glm.hpp>

namespace Bengine {
    
    class GUI
    {
    public:
        void init(const std::string& resourceDirectory);
        void destroy();
        
        void draw();
        void update();
        
        void setMouseCursor(const std::string& mouseFile);
        void showMouseCursor();
        void hideMouseCursor();
        
        void onSDLEvent( SDL_Event& e);

        void loadScheme(const std::string& schemeFile);
        void setFont(const std::string& fontFile);
        
        CEGUI::Window* createWidget(const std::string& type,
                                    const glm::vec4& destRectPerct,
                                    const glm::vec4& destRectPix,
                                    const std::string& name = "");
        
        CEGUI::Window* createWidget(CEGUI::Window* parent,
                                    const std::string& type,
                                    const glm::vec4& destRectPerc,
                                    const glm::vec4& destRectPix,
                                    const std::string& name = "");

        
        static void setWidgetDestRect(CEGUI::Window* widget,
                                 const glm::vec4& destRectPerct,
                                 const glm::vec4& destRectPix);
        
        // Getters
        static CEGUI::OpenGL3Renderer* getRenderer() { return renderer_; }
        const CEGUI::GUIContext* getContext() const {return context_; }
        
    private:
        static CEGUI::OpenGL3Renderer* renderer_;
        
        CEGUI::GUIContext* context_ = nullptr;
        
        CEGUI::Window* root_ = nullptr;
        
        unsigned int lastTime_ = 0;
    };
}

#endif /* GUI_hpp */
