// DEPRECATED, KEEPING FOR REFERENCE, USE MUSICDATABASE.CPP


#include <iostream>
#include <fstream>
#include <sstream>
#include <queue>
#include "MusicObject.h"
#include "ParsingCSV.h"

//comparator for the max-heap priority queue
struct CompareRank {
    bool operator()(const MusicObject& a, const MusicObject& b) {
        return a.rankScore < b.rankScore; //Maxheap higher rank comes first
    }
};

void processData(const std::string& file, int moodChoice, int tempoChoice, int instrumentalnessChoice){ //could also pass in the map/n-ary tree 
    std::ifstream inputFile(file);

    std::priority_queue<MusicObject, std::vector<MusicObject>, CompareRank> maxHeap;

    std::string line;
    int lineCount = 0; //for testing
   
    std::getline(inputFile, line);  // Skip header

    // Read and process each line of the CSV
    while (std::getline(inputFile, line) && lineCount<20) {
        lineCount++;

        std::string artistName, songName, temp, trackID;
        float bpm, valence, energy, instrumentalness;

        std::istringstream stream(line);

        std::getline(stream, temp, ',');            //line number
        std::getline(stream, temp, ',');            //track ID
        trackID = std::stof(temp);
        std::getline(stream, artistName, ',');      // ARTIST NAME
        std::getline(stream, temp, ',');            //album name
        std::getline(stream, songName, ',');        // SONG NAME
        std::getline(stream, temp, ',');            //popularity
        std::getline(stream, temp, ',');            //duration
        std::getline(stream, temp, ',');            //explicit
        std::getline(stream, temp, ',');            //danceability
        std::getline(stream, temp, ',');           
        energy = std::stof(temp);                   // ENERGY as float
        std::getline(stream, temp, ',');            //key
        std::getline(stream, temp, ',');            //loudness
        std::getline(stream, temp, ',');            //mode
        std::getline(stream, temp, ',');            //speechiness 
        std::getline(stream, temp, ',');            //acousticness
        
        std::getline(stream, temp, ','); 
        instrumentalness = std::stof(temp);         // INSTRUMENTALNESS as float
        
        std::getline(stream, temp, ',');            //liveness
        
        std::getline(stream, temp, ',');
        valence = std::stof(temp);                  // VALENCE as float

        std::getline(stream, temp, ',');            // BPM
        bpm = std::stof(temp);

        std::getline(stream, temp, ',');            //time signature
        std::getline(stream, temp, ',');            //genre
        
        
       

        // Create MusicObject with parsed data
        MusicObject song(artistName, songName, trackID, bpm, valence, energy, instrumentalness);

        std::cout << "Artist: " << song.ArtistName << ", Name: " << song.SongName << ", Energy: "
            << song.energy << ", Instrumentalness: " << song.instrumentalness << ", Valance: "
            << song.valence << ", BPM: " << song.bpm << ", Mood: " << song.mood << ", Hash: " << song.filterHash;

        // only calculate rank if the song matches user input parameters
        if (song.filterHash == std::to_string(moodChoice) + std::to_string(tempoChoice) + std::to_string(instrumentalnessChoice)) {
            song.calculateRankScore(moodChoice, tempoChoice, instrumentalnessChoice);

            //push song obj to priority queue (max heap) here
            maxHeap.push(song);
            std::cout << ", Rank: " << song.rankScore;
        }
        std::cout << std::endl;

    }


    inputFile.close();

    //displays the top 20 ranked songs from max-heap'
    std::cout << "\nTop 20 Songs";
    int rank = 1;
    while(!maxHeap.empty() && rank <=20){
        MusicObject topSong = maxHeap.top();
        maxHeap.pop();

        std::cout << rank << ". Artist: " << topSong.ArtistName
        << ", Song: " << topSong. SongName
        <<", Rank: " << topSong.rankScore << std::endl;
    }
}