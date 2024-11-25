#pragma once
#include <iostream>
#ifndef MUSICOBJECT_H
#define MUSICOBJECT_H


struct MusicObject {
	std::string ArtistName;
	std::string SongName;
	float bpm = 0.0f;
	float valence = 0.0f;
	//float loudness = 0.0f;
	float energy = 0.0f;
	float instrumentalness = 0.0f;
	//float speechiness = 0.0f;
	//float acousticness = 0.0f; 
	//std::string songGenre;

	//int mood;
	std::string filterHash;

	//int SongMood(int valence, int energy); // new idea, we're gonna have it return a regular int from 0 to 3 based on the moods
	//std::string filterHash(int SongMood, float bpm, float instrumentalness);

	int calculateMood();
	void calculateHash();

	MusicObject(const std::string& artist, const std::string& song, float bpm, float valence, 
                float energy, float instrumentalness);
   
}; 
#endif


    // actually i'm not sure if i should make this pre-process the hash values

    //i think we have to wait for user input
// yeah, but part of the point was to make the program filter out a set to draw the top 20 results from
	// actually yk we'll work on that later


	

	// next two things to work on are probably the main database and then the csv parser
	// i'll get the code for the parser over ASAP and we'll figure out integration from there