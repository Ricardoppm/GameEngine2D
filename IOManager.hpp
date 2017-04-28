//
//  IOManager.hpp
//  OPENGL
//
//  Created by Ricardo Martins on 11/04/2017.
//  Copyright © 2017 Ricardo Martins. All rights reserved.
//

#ifndef IOManager_hpp
#define IOManager_hpp

#include <vector>
#include <string>

namespace Bengine {

    struct DirEntry {
        std::string path;
        bool isDirectory;
    };
    
    class IOManager
    {
    public:
        static bool readFileToBuffer(std::vector<unsigned char>& buffer, std::string filePath);
        
        static bool readFileToBuffer(std::string& buffer, std::string filePath);

        // Gets all directory entries in the directory specified by path and stores in rvEntries.
        // Returns false if path is not a directory.
        static bool getDirectoryEntries(const char* path, std::vector<DirEntry>& rvEntries);
        static bool makeDirectory(const char* path);
    };
}

#endif /* IOManager_hpp */
