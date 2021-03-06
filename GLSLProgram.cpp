//
//  GLSLProgram.cpp
//  OPENGL
//
//  Created by Ricardo Martins on 10/04/2017.
//  Copyright © 2017 Ricardo Martins. All rights reserved.
//

#include "GLSLProgram.hpp"

#include <fstream>
#include <vector>
#include <iostream>

#include "errors.hpp"
#include "IOManager.hpp"

namespace Bengine {

    GLSLProgram::GLSLProgram() {}

    GLSLProgram::~GLSLProgram(){}

    void GLSLProgram::compileShaders(const std::string &vertexShaderFilePath, const std::string &fragmentShaderFilePath)
    {
        std::string vertSource;
        std::string fragSource;
        
        IOManager::readFileToBuffer(vertSource, vertexShaderFilePath );
        IOManager::readFileToBuffer(fragSource, fragmentShaderFilePath );

        compileShadersFromSource(vertSource.c_str(), fragSource.c_str());
    }

    void GLSLProgram::compileShadersFromSource(const char *vertexSource, const char *fragmentSource)
    {
        //Get a program object.
        programID_ = glCreateProgram();
        
        vertexShaderID_ = glCreateShader(GL_VERTEX_SHADER);
        if( vertexShaderID_==0)
            fatalError("Vertex shader failed to be created");
        
        fragmentShaderID_ = glCreateShader(GL_FRAGMENT_SHADER);
        if( fragmentShaderID_ ==0)
            fatalError("Fragment shader failed to be created");
        
        compileShader(vertexSource, "Vertex shader" , vertexShaderID_);
        compileShader(fragmentSource, "Fragment Shader", fragmentShaderID_);

    }
    
    void GLSLProgram::linkShaders()
    {
        //Vertex and fragment shaders are successfully compiled.
        //Now time to link them together into a program.
       
        
        //Attach our shaders to our program
        glAttachShader(programID_, vertexShaderID_);
        glAttachShader(programID_, fragmentShaderID_);
        
        //Link our program
        glLinkProgram(programID_);
        
        //Note the different functions here: glGetProgram* instead of glGetShader*.
        GLint isLinked = 0;
        glGetProgramiv(programID_, GL_LINK_STATUS, (int *)&isLinked);
        if(isLinked == GL_FALSE)
        {
            GLint maxLength = 0;
            glGetProgramiv(programID_, GL_INFO_LOG_LENGTH, &maxLength);
            
            //The maxLength includes the NULL character
            std::vector<GLchar> errorLog(maxLength);
            glGetProgramInfoLog(programID_, maxLength, &maxLength, &errorLog[0]);
            
            //We don't need the program anymore.
            glDeleteProgram(programID_);
            //Don't leak shaders either.
            glDeleteShader(vertexShaderID_);
            glDeleteShader(fragmentShaderID_);
            
            std::printf("%s\n", &(errorLog[0]));
            fatalError("Shader failed to link!");
        }
        
        //Always detach shaders after a successful link.
        glDetachShader(programID_, vertexShaderID_);
        glDetachShader(programID_, fragmentShaderID_);
        
        glDeleteShader(vertexShaderID_);
        glDeleteShader(fragmentShaderID_);
    }

    void GLSLProgram::addAttribute(const std::string &attributeName)
    { 
        glBindAttribLocation(programID_, numAttributes_++, attributeName.c_str());
    }

    GLint GLSLProgram::getUniformLocation( const std::string& uniformName)
    {
        GLint location = glGetUniformLocation(programID_, uniformName.c_str());
        if( location == GL_INVALID_INDEX){
            fatalError("Uniform " + uniformName + "not found in shader!");
        }
        return location;
    }


    void GLSLProgram::use()
    {
        glUseProgram(programID_);
        for(int i=0; i<numAttributes_; i++){
            glEnableVertexAttribArray(i);
        }
    }

    void GLSLProgram::unuse()
    {
        glUseProgram(0);
        for(int i=0; i<numAttributes_; i++){
            glDisableVertexAttribArray(i);
        }
        numAttributes_ = 0;
    }

    void GLSLProgram::dispose()
    {
        if(programID_)
            glDeleteProgram(programID_);
    }
    
    void GLSLProgram::compileShader(const char* source, const std::string& name, GLuint id)
    {
        glShaderSource(id, 1, &source, nullptr);
        
        glCompileShader(id);
        
        GLint success = 0;
        glGetShaderiv(id, GL_COMPILE_STATUS, &success);
        if( success == GL_FALSE){
            GLint maxLength = 0;
            glGetShaderiv(id, GL_INFO_LOG_LENGTH, &maxLength);
            
            // The maxLength includes the NULL character
            std::vector<GLchar> errorLog(maxLength);
            glGetShaderInfoLog(id, maxLength, &maxLength, &errorLog[0]);
            
            // Provide the infolog in whatever manor you deem best.
            // Exit with failure.
            glDeleteShader(id); // Don't leak the shader.
            
            std::printf("%s\n", &(errorLog[0]));
            fatalError("Shader " + name + " failed to compile");
        }
    }
}
