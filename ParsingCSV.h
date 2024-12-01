#pragma once
#include <string>
#include <vector>
#include "MusicObject.h"
#include "UnorderedMap.h"

#ifndef PARSINGCSV_H
#define PARSINGCSV_H


//void processData(const std::string& file, int moodChoice, int tempoChoice, int instrumentalnessChoice);
void processData(const std::string& file, int moodChoice, int tempoChoice, int instrumentalnessChoice, 
     UnorderedMapStorage* mapStorage, UnorderedMapStorage* treeStorage, const std::string& userHash);

#endif