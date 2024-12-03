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

void displayTopSongs(const std::string& hashInput, bool infoResolution) {

    std::vector<std::string> moods = { "Happy", "Sad", "Angry", "Focused" };
    auto it = songMap.find(hashInput);
    if (it != songMap.end()) {
        const std::unordered_set<std::string>& trackIDs = it->second.trackIDs;
        auto& queue = it->second.queue;

        int rank = 1;
        int count = 0;

        //pop top 20 songs & display
        std::cout << "\nList of songs matching hash " << hashInput << ":\n" << std::endl;
        while (!queue.empty() && count < 20) {
            const MusicObject& topSong = queue.top();
            std::cout << rank << ". Song Name: " << std::setw(32) << std::left << topSong.SongName
                << " | Artist: " << std::setw(24) << std::left << topSong.ArtistName
                << " | Genre: " << std::setw(16) << std::left << topSong.genre;
                if (infoResolution) {
                    std::cout << " | BPM: " << std::setw(8) << std::left << topSong.bpm
                        << " | Mood: " << std::setw(moods[topSong.mood].size()) << std::left << moods[topSong.mood] << " (" << topSong.mood << ")"
                        << " | Valence: " << std::setw(6) << std::left << topSong.valence
                        << " | Instrumentalness: " << std::setw(4) << std::left << topSong.instrumentalness
                        << " | Energy: " << std::setw(4) << std::left << topSong.energy
                        << " | Rank Score: " << std::setw(8) << std::left << topSong.rankScore;
                }
                std::cout << "\n";
            queue.pop();
            rank++;
            count++;
        }
    
    } else {
        std::cout << "No songs found with hash: " << hashInput << std::endl;
    }
}



}; 