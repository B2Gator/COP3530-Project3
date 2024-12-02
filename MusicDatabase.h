#pragma once
#include <set>
#include <unordered_map>
#include <string>
#include <vector>
#include "MusicObject.h"
#ifndef MUSICDATABASE_H
#define MUSICDATABASE_H
struct MusicDB {
	// the idea here is tuple<trackID, songName, musicObject> for identification within the sets
	std::set<std::tuple<std::string, std::string, MusicObject>> allSongs;
	std::unordered_map<std::string, std::set<std::tuple<std::string, std::string, MusicObject>>> subsets;
	void processData(const std::string& file, int moodChoice, int tempoChoice, int instrumentalnessChoice);
private:
	std::vector<std::string> parseLine(const std::string& line);
};
#endif
