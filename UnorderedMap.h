#include <unordered_map>
#include "MusicObject.h"
#include "SongHeaps.h"



class UnorderedMapStorage {
public:

    std::unordered_map<std::string, SongCollection> songMap;

    void addSong(const MusicObject& song) {
    
       auto& collection = songMap[song.filterHash];
        if (collection.trackIDs.find(song.trackID) == collection.trackIDs.end()) {
            collection.trackIDs.insert(song.trackID);
            collection.queue.push(song);
        }
    }

void displayTopSongs(const std::string& hashInput) {
    std::cout << "Generated userHash: " << hashInput << std::endl;
    auto it = songMap.find(hashInput);
    if (it != songMap.end()) {
        auto& [trackIDs, queue] = it->second; 
        auto tempQueue = queue;  // Make a copy to iterate and preserve the original

        int rank = 1;
        while (!tempQueue.empty() && rank <= 20) {
            const MusicObject& topSong = tempQueue.top();
            std::cout << rank << ". Artist: " << topSong.ArtistName
                      << ", Name: " << topSong.SongName
                      << " | Rank: " << topSong.rankScore<< " | Hash: " << topSong.filterHash << "\n";
            tempQueue.pop();
            rank++;
        }
    } else {
        std::cout << "No songs found with hash: " << hashInput << std::endl;
    }
}



}; 