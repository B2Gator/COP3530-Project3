#pragma once
#include <iostream>
#ifndef MUSICOBJECT_H
#define MUSICOBJECT_H


struct MusicObject {
	std::string ArtistName;
	std::string SongName;
	float bpm = 0.0f;
	float valence = 0.0f;
	float energy = 0.0f;
	float instrumentalness = 0.0f;
	
	std::string filterHash;

	int calculateMood();
	void calculateHash();

	MusicObject(const std::string& artist, const std::string& song, float bpm, float valence, 
                float energy, float instrumentalness);
   
}; 
#endif
