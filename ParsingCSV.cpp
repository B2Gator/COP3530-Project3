#include <iostream>
#include <fstream>
#include <sstream>
#include "ParsingCSV.h"


void processData(const std::string& file){
    std::ifstream inputFile(file);

    std::string line;
    int lineCount = 0; //for testing
   
    std::getline(inputFile, line);  // Skip header

    // Read and process each line of the CSV
    while (std::getline(inputFile, line) && lineCount<20) {
        lineCount++;

        std::string artistName, songName, temp;
        float bpm, valence, energy, instrumentalness;

        std::istringstream stream(line);

        std::getline(stream, temp, ',');            //line number
        std::getline(stream, temp, ',');            //track ID
        std::getline(stream, artistName, ',');    // ARTIST NAME
        std::getline(stream, temp, ',');            //album name
        std::getline(stream, songName, ',');      // SONG NAME
        std::getline(stream, temp, ',');            //popularity
        std::getline(stream, temp, ',');            //duration
        std::getline(stream, temp, ',');            //explicit
        std::getline(stream, temp, ',');            //danceability
        std::getline(stream, temp, ',');           
        energy = std::stof(temp);                  // ENERGY as float
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

        std::getline(stream, temp, ',');          // BPM
        bpm = std::stof(temp);

        std::getline(stream, temp, ',');        //time signature
        std::getline(stream, temp, ',');        //genre
        
        
       

        // Create MusicObject with parsed data
        MusicObject song(artistName, songName, bpm, valence, energy, instrumentalness);

        std::cout << "Artist: " << song.ArtistName << ", Name: "<< song.SongName << ", Energy: "<< song.energy << ", Instrumentalness: "<< song.instrumentalness << ", Valance: "<< song.valence  << ", BPM: "<< song.bpm  << std::endl;
    }


}



