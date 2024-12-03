
#include <vector>
#include <string>
#include "SongHeaps.h" 
#include "Tree.h"


NaryTreeStorage::NaryTreeStorage() {
    root = new NaryTreeNode();  // Initializing root node
}

NaryTreeStorage::~NaryTreeStorage() {
    deleteTree(root);
}

// deletes nodes
void NaryTreeStorage::deleteTree(NaryTreeNode* node) {
    if (!node) return;

    for (NaryTreeNode* child : node->children) {
        deleteTree(child);
    }

    delete node;
}

// Find or create a node based on the hash
NaryTreeNode* NaryTreeStorage::findOrCreateNode(NaryTreeNode* current, const std::string& hashInput) {
    NaryTreeNode* node = current;

    // Iterate over each digit in the hash to navigate/expand the tree
    for (char c : hashInput) {
        int index;
        if (c == '0') 
            index = 0;
        else if (c == '1')
            index = 1;
        else if (c == '2') 
            index = 2;
        else if (c == '3')
            index = 3;
        
        // Ensure that the current node has enough children
        if (node->children.size() <= index) {
            // Expand the children vector to include more children as needed
            node->children.resize(index + 1, nullptr);
        }
        
        // create child if need be
        if (!node->children[index]) {
            node->children[index] = new NaryTreeNode();
        }

        // Move to the next node in the path
        node = node->children[index];
    }

    return node;
}

// Add a song to the tree at the appropriate location based on the hash
void NaryTreeStorage::addSong(const MusicObject& song, const std::string& hashInput) {
    NaryTreeNode* node = findOrCreateNode(root, hashInput);
    std::pair<std::string, std::string> TitleArtist = std::make_pair(song.SongName, song.ArtistName);

    if (node->songCollection.trackIDs.find(song.trackID) == node->songCollection.trackIDs.end()
        &&
        (node->songCollection.SongArtistNames.find(TitleArtist) == node->songCollection.SongArtistNames.end())) {
        node->songCollection.SongArtistNames.insert(TitleArtist);
        node->songCollection.queue.push(song);  // Add the song to the priority queue at the leaf node
        node->songCollection.trackIDs.insert(song.trackID);  // Add ID to set
    }

}

void NaryTreeStorage::displayTopSongs(const std::string& hashInput) {
   
    NaryTreeNode* node = root; //starting node
    
    for (char c : hashInput) {
        int index;
        if (c == '0') 
            index = 0;
        else if (c == '1')
            index = 1;
        else if (c == '2') 
            index = 2;
        else if (c == '3')
            index = 3;
        
        // Move to the child node
        node = node->children[index];
    }

    bool foundMatch = false;

    // check if node exists
    if (!node->songCollection.queue.empty()) {

        int rank = 1;
        int count = 0;
        std::vector<std::string> moods = { "Happy", "Sad", "Angry", "Focused" };
        // Output up to 20 top songs
        while (!node->songCollection.queue.empty() && count < 20) {
            const MusicObject& song = node->songCollection.queue.top();
             if (song.filterHash == hashInput) {
                foundMatch = true;
                 std::cout << rank << ". Song Name: " << song.SongName
                     << " | Artist: " << song.ArtistName
                     << " | BPM: " << song.bpm
                     << " | Mood: " << moods[song.mood] << " (" << song.mood << ")"
                     << " | Valence: " << song.valence
                     << " | Instrumentalness: " << song.instrumentalness
                     << " | Energy: " << song.energy
                     << " | Hash: " << std::stoi(song.filterHash) + 111
                     << " | Rank Score: " << song.rankScore << "\n";
                rank++;
                count++;
            }
            node->songCollection.queue.pop();
        }
    } 
        
    else if (!foundMatch){
        std::cout << "No songs found with hash: " << std::stoi(hashInput) + 111 << std::endl;
    }
}

