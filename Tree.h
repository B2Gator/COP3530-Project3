
#pragma once
#include <vector>
#include <string>
#include "SongHeaps.h" 

// Represents a node in N-ary tree
struct NaryTreeNode {
    std::vector<NaryTreeNode*> children;  
    SongCollection songCollection;        // Priority queue for songs
};


class NaryTreeStorage {
    NaryTreeNode* root;
    void deleteTree(NaryTreeNode* node);
    NaryTreeNode* findOrCreateNode(NaryTreeNode* current, const std::string& hashInput);

    public:
        NaryTreeStorage();
        ~NaryTreeStorage();

        void addSong(const MusicObject& song, const std::string& hashInput);
        void displayTopSongs(const std::string& hashInput, bool infoResolution);
        
};

