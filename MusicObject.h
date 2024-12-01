#pragma once
#include <iostream>
//#include <array>
#include <vector>
#ifndef MUSICOBJECT_H
#define MUSICOBJECT_H


struct MusicObject {
	std::string ArtistName;
	std::string SongName;
	float bpm = 0.0f;
	float valence = 0.0f;
	float energy = 0.0f;
	float instrumentalness = 0.0f;
	
	int mood;
	std::string filterHash;

	float rankScore = 0.0f;

	int calculateMood();
	void calculateHash();

	float calculateMoodRank(int moodChoice);
	float calculateTempoRank(int tempoChoice);
	float calculateInstrumentalnessRank(int instrumentalnessChoice);
	void calculateRankScore(int moodChoice, int tempoChoice, int instrumentalnessChoice);

	MusicObject(const std::string& artist, const std::string& song, float bpm, float valence, 
                float energy, float instrumentalness);
   

   private:
    std::vector<float> idealValence = {1.0f, 0.0f, 1.0f, 0.0f}; // Happy, Sad, Chill, Angry
    std::vector<float> idealEnergy = {1.0f, 0.0f, 0.0f, 1.0f};
	std::vector<float> idealTempo = {25.0f, 75.0f, 125.0f, 175.0f}; //slow, moderate, fast, very fast
	std::vector<float> idealInstrumentalness = {0.0f, 0.35f, 0.65f, 1.0f}; //mostly vocals, moderate vocals, less vocals, little/no vocals
}; 

//create another struct for the user choices (use to rank songs)
struct UserChoice {
	int moodChoice;
	int tempoChoice;
	int instrumentalnessChoice;

};



#endif
