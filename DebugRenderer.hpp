//
//  DebugRenderer.hpp
//  NinjaPlatformer
//
//  Created by Ricardo Martins on 24/04/2017.
//  Copyright © 2017 Ricardo Martins. All rights reserved.
//

#ifndef DebugRenderer_hpp
#define DebugRenderer_hpp

#include <glm/glm.hpp>
#include <vector>

#include "GLSLProgram.hpp"
#include "Vertex.h"

namespace Bengine {
    
    class DebugRenderer
    {
    public:
        DebugRenderer();
        ~DebugRenderer();
        
        void init();
        void dispose();
        
        void end();
        
        void drawLine(const glm::vec2& a, const glm::vec2& b, const ColorRGBA8& color);

        void drawBox(const glm::vec4& destRect, const ColorRGBA8& color, float angle);
        
        void drawCircle(const glm::vec2& center, const ColorRGBA8& color, float radius);
        
        void render(const glm::mat4& projectionMatrix, float lineWidth);
        
        struct DebugVertex{
            glm::vec2 position;
            ColorRGBA8 color;
        };
        
        
    private:
        GLSLProgram program_;
        std::vector<DebugVertex> verts_;
        std::vector< GLuint > indices_;
        GLuint vbo_ = 0, vao_ = 0, ibo_ = 0;
        
        int numElements_ = 0;
    };
}


#endif /* DebugRenderer_hpp */
