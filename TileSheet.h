//
//  TileSheet.h
//  NinjaPlatformer
//
//  Created by Ricardo Martins on 25/04/2017.
//  Copyright © 2017 Ricardo Martins. All rights reserved.
//

#ifndef TileSheet_h
#define TileSheet_h

#include <glm/glm.hpp>

#include "GLTexture.h"

namespace Bengine {
    class TileSheet
    {
    public:
        void init(const GLTexture& texture, const glm::ivec2& tileDims){
            this->texture = texture;
            this->dims = tileDims;
        }
        
        glm::vec4 getUVS(int index){
            int xTile = index % dims.x;
            int yTile = index / dims.x;
            
            glm::vec4 uvRect;
            uvRect.x = xTile / (float)dims.x;
            uvRect.y = yTile / (float)dims.y;
            uvRect.z = 1.f / dims.x;
            uvRect.w = 1.f / dims.y;
            
            return uvRect;
        }
        
        GLTexture texture;
        glm::ivec2 dims;
    };
}


#endif /* TileSheet_h */
