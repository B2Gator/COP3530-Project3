#pragma once
#include <iostream>
#include <iomanip>
#include <array>
#include <string>
#ifndef MUSICOBJECT_H
#define MUSICOBJECT_H


struct MusicObject {
	std::string ArtistName;
	std::string SongName;
	std::string trackID;
	std::string genre;
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

	MusicObject(const std::string& artist, const std::string& song, const std::string& trackID, const std::string& genre,
		float bpm, float valence, float energy, float instrumentalness);
	MusicObject(const MusicObject& other);
	MusicObject& operator=(const MusicObject& other);
	MusicObject(MusicObject&& other) noexcept;
	MusicObject& operator=(MusicObject&& other) noexcept;
	bool operator<(const MusicObject& other) const {
		return trackID < other.trackID;
	}
   

   private:
    const std::array<float, 4> idealValence = {1.0f, 0.0f, 1.0f, 0.0f}; // Happy, Sad, Chill, Angry
    const std::array<float, 4> idealEnergy = {1.0f, 0.0f, 0.0f, 1.0f};
	const std::array<float, 4> idealTempo = {175.0f, 125.0f, 75.0f, 25.0f}; // very fast, fast, moderate, slow
	const std::array<float, 4> idealInstrumentalness = {0.0f, 0.35f, 0.65f, 1.0f}; // mostly vocals, moderate vocals, less vocals, little/no vocals
}; 

//create another struct for the user choices (use to rank songs)
struct UserChoice {
	int moodChoice;
	int tempoChoice;
	int instrumentalnessChoice;

};



#endif
