#pragma once
#include <set>
#include <unordered_map>
#include <string>
#include <vector>
#include "MusicObject.h"
#include "UnorderedMap.h"
#ifndef MUSICDATABASE_H
#define MUSICDATABASE_H
struct MusicDB {
	void processData(const std::string& file, int moodChoice, int tempoChoice, int instrumentalnessChoice, UnorderedMapStorage* mapStorage, UnorderedMapStorage* treeStorage, const std::string& userHash);
private:
	std::vector<std::string> parseLine(const std::string& line);
};
#endif
	