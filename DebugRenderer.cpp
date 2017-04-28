//
//  DebugRenderer.cpp
//  NinjaPlatformer
//
//  Created by Ricardo Martins on 24/04/2017.
//  Copyright © 2017 Ricardo Martins. All rights reserved.
//

#include "DebugRenderer.hpp"

namespace  {
    const char* VERT_SOURCE = R"(#version 150
    //The vertex shader operates on each vertex
    
    //input data from the VBO. Each vertex is 2 floats
    in vec2 vertexPosition;
    in vec4 vertexColor;
    
    out vec2 fragmentPosition;
    out vec4 fragmentColor;
    
    uniform mat4 P;
    
    void main() {
        //Set the x,y position on the screen
        gl_Position.xy = (P * vec4(vertexPosition, 0.0, 1.0)).xy;
        //the z position is zero since we are in 2D
        gl_Position.z = 0.0;
        
        //Indicate that the coordinates are normalized
        gl_Position.w = 1.0;
        
        fragmentPosition = vertexPosition;
        
        fragmentColor = vertexColor;
    })";
    
    const char* FRAG_SOURCE = R"(#version 150
    //The fragment shader operates on each pixel in a given polygon
    
    in vec2 fragmentPosition;
    in vec4 fragmentColor;
    
    //This is the 3 component float vector that gets outputted to the screen
    //for each pixel.
    out vec4 color;
    
    
    void main() {
        
        color = fragmentColor;
    })";
}



namespace Bengine {
    
    DebugRenderer::DebugRenderer()
    {
        // empty
    }
    
    DebugRenderer::~DebugRenderer()
    {
        dispose();
    }
    
    void DebugRenderer::init()
    {
        // Shader initialization
        program_.compileShadersFromSource(VERT_SOURCE, FRAG_SOURCE);
        program_.addAttribute("vertexPosition");
        program_.addAttribute("vertexColor");
        program_.linkShaders();
        
        // Set up buffers
        glGenVertexArrays(1, &vao_);
        glGenBuffers(1, &vbo_);
        glGenBuffers(1, &ibo_);

        glBindVertexArray(vao_);
        glBindBuffer(GL_ARRAY_BUFFER, vbo_);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo_);
        
        // Vertex attrib pointers
        glEnableVertexAttribArray(0);
        glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(DebugVertex), (void*)offsetof(DebugVertex, position));
        glEnableVertexAttribArray(1);
        glVertexAttribPointer(1, 4, GL_UNSIGNED_BYTE, GL_TRUE, sizeof(DebugVertex), (void*)offsetof(DebugVertex, color));

        
        glBindVertexArray(0);
    }
    
    void DebugRenderer::end()
    {
        glBindBuffer(GL_ARRAY_BUFFER, vbo_);
        // Orphan the buffer
        glBufferData(GL_ARRAY_BUFFER, verts_.size() * sizeof(DebugVertex), nullptr, GL_DYNAMIC_DRAW);
        // Upload data
        glBufferSubData(GL_ARRAY_BUFFER, 0,  verts_.size() * sizeof(DebugVertex), verts_.data());
        glBindBuffer(GL_ARRAY_BUFFER, 0);
        
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo_);
        // Orphan the buffer
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices_.size() * sizeof(GLuint), nullptr, GL_DYNAMIC_DRAW);
        // Upload data
        glBufferSubData(GL_ELEMENT_ARRAY_BUFFER, 0,  indices_.size() * sizeof(GLuint), indices_.data());
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

        numElements_ = indices_.size();
        indices_.clear();
        verts_.clear();
    }
    
    
    glm::vec2 rotatePoint(glm::vec2 position, float angle)
    {
        glm::vec2 newVector;
        
        newVector.x = position.x * cos(angle) - position.y * sin(angle);
        newVector.y = position.x * sin(angle) + position.y * cos(angle);
        
        return newVector;
    }

    void Bengine::DebugRenderer::drawLine(const glm::vec2& a, const glm::vec2& b, const ColorRGBA8& color) {
        int i = verts_.size();
        verts_.resize(verts_.size() + 2);
        
        verts_[i].position = a;
        verts_[i].color = color;
        verts_[i + 1].position = b;
        verts_[i + 1].color = color;
        
        indices_.push_back(i);
        indices_.push_back(i + 1);
        }
    
    void DebugRenderer::drawBox(const glm::vec4 &destRect, const Bengine::ColorRGBA8 &color, float angle)
    {
        int i = verts_.size();
        verts_.resize( verts_.size() + 4);

        
        // Center sprite on origin
        glm::vec2 halfDims(destRect.z / 2.f , destRect.w / 2.f);
        
        glm::vec2 tl(-halfDims.x, halfDims.y);
        glm::vec2 bl(-halfDims.x, -halfDims.y);
        glm::vec2 br(halfDims.x, -halfDims.y);
        glm::vec2 tr(halfDims.x, halfDims.y);
        
        glm::vec2 positionOffset( destRect.x, destRect.y);
        
        // Rotate Points and pass point from center to top left
        verts_[i].position = rotatePoint(tl, angle) + halfDims + positionOffset;
        verts_[i+1].position = rotatePoint(bl, angle) + halfDims + positionOffset;
        verts_[i+2].position = rotatePoint(br, angle) + halfDims + positionOffset;
        verts_[i+3].position = rotatePoint(tr, angle) + halfDims + positionOffset;
        
        for (int j = i; j < i +4; j++) {
            verts_[j].color = color;
        }
        
        indices_.reserve(indices_.size() + 8);
        indices_.push_back(i);
        indices_.push_back(i + 1);
        
        indices_.push_back(i + 1);
        indices_.push_back(i + 2);
        
        indices_.push_back(i + 2);
        indices_.push_back(i + 3);
        
        indices_.push_back(i + 3);
        indices_.push_back(i);


    }
    
    void DebugRenderer::drawCircle(const glm::vec2 &center, const Bengine::ColorRGBA8 &color, float radius)
    {
        static const int NUM_VERTS = 100;
    
        
        int start = verts_.size();
        verts_.resize( verts_.size() + NUM_VERTS);
        
        // Create vertices
        for (int i = 0; i < NUM_VERTS; i++) {
            float angle = ((float)i / NUM_VERTS) * 2.f * M_PI;
            verts_[start + i].position.x = cos(angle) * radius + center.x;
            verts_[start + i].position.y = sin(angle) * radius + center.y;
            verts_[start + i].color = color;
        }
        // Set up indices
        indices_.reserve(indices_.size() + 2*NUM_VERTS);
        for (int i = 0; i < NUM_VERTS-1; i++) {
            indices_.push_back(start + i);
            indices_.push_back(start + i + 1);
        }
        indices_.push_back(start + NUM_VERTS - 1);
        indices_.push_back(start);
        
        

    


    }
    
    void DebugRenderer::render(const glm::mat4& projectionMatrix, float lineWidth)
    {
        program_.use();
        
        // Camera matrix
        GLuint cameraUniform = program_.getUniformLocation("P");
        glUniformMatrix4fv(cameraUniform, 1, GL_FALSE, &projectionMatrix[0][0]);
        
        glLineWidth(lineWidth);
        
        glBindVertexArray(vao_);
        glDrawElements(GL_LINES, numElements_, GL_UNSIGNED_INT, 0);
        glBindVertexArray(0);
        
        program_.unuse();
    }
    
    void DebugRenderer::dispose()
    {
        if (vao_) {
            glDeleteVertexArrays(1, &vao_);
        }
        if (vbo_) {
            glDeleteBuffers(1, &vbo_);
        }
        if (ibo_) {
            glDeleteBuffers(1, &ibo_);
        }
        program_.dispose();
    }
    
}
