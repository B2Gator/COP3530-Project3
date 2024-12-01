#include <unordered_map>
#include <queue>
#include "MusicObject.h"
#include "CompareRank.h"

class UnorderedMapStorage {
public:
    std::unordered_map<std::string, std::priority_queue<MusicObject, std::vector<MusicObject>, CompareRank>> songMap;

    void addSong(const MusicObject& song) {
        songMap[song.filterHash].push(song);
        //std::cout << "Song added to heap" << std::endl;
    }

    void displayTopSongs(const std::string& hashInput) {
        auto it = songMap.find(hashInput);
        

        if (it != songMap.end()) {
            auto tempQueue = it->second;
            int rank = 1;
            while (!tempQueue.empty() && rank <= 20) {
                const MusicObject& topSong = tempQueue.top();
                std::cout << rank << ". " << topSong.ArtistName << " - " << topSong.SongName
                        << " | Rank: " << topSong.rankScore << std::endl;
                tempQueue.pop();
                rank++;
            }

    } 
    
    else {
        std::cout << "No songs found with hash: " << hashInput << std::endl;
    }
}
};