#pragma once
#include <set>
#include <unordered_map>
#include <string>
#include <vector>
#include "MusicObject.h"
#include "UnorderedMap.h"
#include "Tree.h"


#ifndef MUSICDATABASE_H
#define MUSICDATABASE_H
struct MusicDB {
	void processData(const std::string& file, int moodChoice, int tempoChoice, int instrumentalnessChoice, UnorderedMapStorage* mapStorage, NaryTreeStorage* treeStorage, const std::string& hashInput);
private:
	std::vector<std::string> parseLine(const std::string& line);
};
#endif
	