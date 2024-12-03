#include <unordered_map>
#include "MusicObject.h"
#include "SongHeaps.h"



class UnorderedMapStorage {
public:

    std::unordered_map<std::string, SongCollection> songMap;

    void addSong(const MusicObject& song) {
        
       std::pair<std::string, std::string> TitleArtist = std::make_pair(song.SongName, song.ArtistName);
       auto& collection = songMap[song.filterHash];
        if (collection.trackIDs.find(song.trackID) == collection.trackIDs.end() &&
            (collection.SongArtistNames.find(TitleArtist) == collection.SongArtistNames.end())) {
            collection.SongArtistNames.insert(TitleArtist);
            collection.trackIDs.insert(song.trackID);
            collection.queue.push(song);
        }

    }

void displayTopSongs(const std::string& hashInput) {

    std::vector<std::string> moods = { "Happy", "Sad", "Angry", "Focused" };
    auto it = songMap.find(hashInput);
    if (it != songMap.end()) {
        const std::unordered_set<std::string>& trackIDs = it->second.trackIDs;
        auto& queue = it->second.queue;

        int rank = 1;
        int count = 0;

        //pop top 20 songs & display
        while (!queue.empty() && count < 20) {
            const MusicObject& topSong = queue.top();
            std::cout << rank << ". Song Name: " << topSong.SongName
                << " | Artist: " << topSong.ArtistName
                << " | BPM: " << topSong.bpm
                << " | Mood: " << moods[topSong.mood] << " (" << topSong.mood << ")"
                << " | Valence: " << topSong.valence
                << " | Instrumentalness: " << topSong.instrumentalness
                << " | Energy: " << topSong.energy
                << " | Hash: " << stoi(topSong.filterHash) + 111
                << " | Rank Score: " << topSong.rankScore << "\n";
            queue.pop();
            rank++;
            count++;
        }
    
    } else {
        std::cout << "No songs found with hash: " << hashInput << std::endl;
    }
}

}; 