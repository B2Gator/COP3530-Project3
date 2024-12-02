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


    auto it = songMap.find(hashInput);
    if (it != songMap.end()) {
        auto& [trackIDs, queue] = it->second;

        int rank = 1;
        int count = 0;

        //pop top 20 songs & display
        while (!queue.empty() && count < 20) {
            const MusicObject& topSong = queue.top();
            std::cout << rank << ". Artist: " << topSong.ArtistName
                      << ", Name: " << topSong.SongName
                      << " | Rank: " << topSong.rankScore 
                      << " | TrackID: " << topSong.trackID 
                      << " | Hash: " << topSong.filterHash << "\n";
            queue.pop();
            rank++;
            count++;
        }
    
    } else {
        std::cout << "No songs found with hash: " << hashInput << std::endl;
    }
}

}; 