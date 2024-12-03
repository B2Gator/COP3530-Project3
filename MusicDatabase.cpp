
#include "MusicDatabase.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <queue>

void MusicDB::processData(const std::string& file, int moodChoice, int tempoChoice, int instrumentalnessChoice, UnorderedMapStorage* mapStorage, NaryTreeStorage* treeStorage, const std::string& hashInput) {
    std::ifstream inputFile(file);
    std::string line;
    int lineCount = 0; //for testing
    std::getline(inputFile, line);  // Skip header
    // Read and process each line of the CSV
    while (std::getline(inputFile, line)) {
        lineCount++;
        std::vector<std::string> fields = parseLine(line);
        if (fields.size() < 15) {
            std::cerr << "Malformed line at " << lineCount << ": " << line << std::endl;
            continue;
        }
        try {
            std::string trackID = fields[1];
            std::string artistName = fields[2];
            std::string songName = fields[4];
            float energy = std::stof(fields[9]);
            float instrumentalness = std::stof(fields[15]);
            float valence = std::stof(fields[17]);
            float bpm = std::stof(fields[18]);
            std::string genre = fields[20];
            
            MusicObject song(artistName, songName, trackID, genre, bpm, valence, energy, instrumentalness);
            song.calculateRankScore(moodChoice, tempoChoice, instrumentalnessChoice);
            
            
            if (mapStorage) {
                mapStorage->addSong(song);
            } 
            else if (treeStorage) { 
                treeStorage->addSong(song, hashInput);
            }
          
        }
        catch (const std::exception& e) {
            std::cerr << std::endl;
            continue;
        }
    }
    inputFile.close();
}
// parses the current CSV line, handles situations with commas and quotation marks
std::vector<std::string> MusicDB::parseLine(const std::string& line) {
    std::vector<std::string> fields;
    std::istringstream stream(line);
    std::string field;
    while (stream.good()) {
        if (stream.peek() == '"') {
            //handle quoted field
            stream.get(); //remove the opening quote
            std::ostringstream quotedField;
            while (true) {
                char c = stream.get();
                if (c == '"') {
                    if (stream.peek() == '"') {
                        //escaped quote (""), so include one quote
                        quotedField.put('"');
                        stream.get(); //consume the second quote
                    }
                    else {
                        //end of quoted field
                        break;
                    }
                }
                else if (c == EOF) {
                    //handle unexpected EOF
                    throw std::runtime_error("malformed CSV: unexpected EOF.");
                }
                else {
                    //add normal characters to the quoted field
                    quotedField.put(c);
                }
            }
            field = quotedField.str();
        }
        else {
            //handle unquoted field
            std::getline(stream, field, ',');
        }
        fields.push_back(field);
        //skip the delimiter after the field
        if (stream.peek() == ',') {
            stream.get();
        }
    }
    return fields;
}