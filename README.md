# GameEngine2D
2D Game Engine - SDL2 / OpenGL

Used frameworks:
  - SDL2
  - SDL2_ttf
  - SDL2_mixer
  - glm
  - OpenGL
  
  Xcode usage:
    
   - Download SDL2       :  https://www.libsdl.org/download-2.0.php
   
   - Download SDL2_ttf   :  https://www.libsdl.org/projects/SDL_ttf/
   
   - Download SDL2_mixer :  https://www.libsdl.org/projects/SDL_mixer/
   
   - Download GLM        :  https://github.com/g-truc/glm/tags
   
   - Link framworks:
        - Xcode -> Project -> Build Phases -> Link Binary with Libraries:  
        - All three should be located on Library/Frameworks
        - Link OpenGL.framework
   
   - Link GLM header file:
        - Xcode -> Project -> Build Settings -> Search Paths -> Header Search Paths
        - Add glm header folder path
        
