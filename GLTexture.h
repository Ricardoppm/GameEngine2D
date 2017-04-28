//
//  GLTexture.h
//  OPENGL
//
//  Created by Ricardo Martins on 11/04/2017.
//  Copyright © 2017 Ricardo Martins. All rights reserved.
//

#ifndef GLTexture_h
#define GLTexture_h

#include <epoxy/gl.h>
#include <OpenGL/gl3.h>

#include <string>

namespace Bengine {

    struct GLTexture
    {
        std::string filePath = "";
        GLuint id;
        int width;
        int height;

    };
}
#endif /* GLTexture_h */
