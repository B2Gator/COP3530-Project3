#include "MusicDatabase.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <queue>



void MusicDB::processData(const std::string& file, int moodChoice, int tempoChoice, int instrumentalnessChoice, UnorderedMapStorage* mapStorage, UnorderedMapStorage* treeStorage, const std::string& userHash) { //could also pass in the map/n-ary tree 
    std::ifstream inputFile(file);

=======
//comparator for the max-heap priority queue
struct CompareRank {
    bool operator()(const MusicObject& a, const MusicObject& b) {
        return a.rankScore < b.rankScore; //Maxheap higher rank comes first
    }
};

void MusicDB::processData(const std::string& file, int moodChoice, int tempoChoice, int instrumentalnessChoice) { //could also pass in the map/n-ary tree 
    std::ifstream inputFile(file);

    std::priority_queue<MusicObject, std::vector<MusicObject>, CompareRank> maxHeap;


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

            MusicObject song(artistName, songName, trackID, bpm, valence, energy, instrumentalness);


            song.calculateRankScore(moodChoice, tempoChoice, instrumentalnessChoice);

            mapStorage->addSong(song);
          
            allSongs.insert(make_tuple(song.trackID, song.SongName, song)); // inserts song into database of all songs
            subsets[song.filterHash].insert(make_tuple(song.trackID, song.SongName, song)); // inserts into subset

            if (song.filterHash == std::to_string(moodChoice) + std::to_string(tempoChoice) + std::to_string(instrumentalnessChoice)) {
                // calculates score for ranking if it matches user input hash
                song.calculateRankScore(moodChoice, tempoChoice, instrumentalnessChoice); 
            }
        }
        catch (const std::exception& e) {
            std::cerr << "error parsing line" << lineCount << ": " << e.what() << std::endl;
            continue;
        }
    }


    inputFile.close();



    //displays the top 20 ranked songs from max-heap
    std::cout << "\nTop 20 Songs"; // ranking functionality has not been re-implemented yet, stop-gap for debugging

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
