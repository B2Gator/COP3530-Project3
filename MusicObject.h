#pragma once
#include <iostream>
#ifndef MUSICOBJECT_H
#define MUSICOBJECT_H


struct MusicObject {
	std::string ArtistName;
	std::string SongName;
	float bpm = 0.0f;
	float Valence = 0.0f;
	float loudness = 0.0f;
	float energy = 0.0f;
	std::string filterHash;
	float instrumentalness = 0.0f;
	float speechiness = 0.0f;
	float acousticness = 0.0f; 
	std::string songGenre;
	int SongMood(int valence, int energy); // new idea, we're gonna have it return a regular int from 0 to 3 based on the moods
	
	

    // actually i'm not sure if i should make this pre-process the hash values

    //i think we have to wait for user input

	// yeah, but part of the point was to make the program filter out a set to draw the top 20 results from
	// actually yk we'll work on that later



	// we'd load in the database before any user input, since we have to load it in anyway

    //how do we actually load the data though. I was looking at an OpenXLSX download thing but idk 
	// we're loading a csv file, which is pretty straightforward. i think i still have leftover parsing code we can cobble in
    //ok cool

	// i hate to cut things short right now but i really have to go. i'll send both the source files over

	// next two things to work on are probably the main database and then the csv parser
	// i'll get the code for the parser over ASAP and we'll figure out integration from there

    //thank you!
    //is there a way we can keep this folder somewhere we can all look at it? 
	// i could probably set up a github repo, though i haven't done that in a hot minute
    // github?
    // i think you can publish it to a new repo directly from here if you go over to the source control on the left
}; 
#endif