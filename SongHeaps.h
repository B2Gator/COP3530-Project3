#pragma once
#include <unordered_set>
#include <queue>
#include <set>
#include "MusicObject.h"


//comparator for the max-heap priority queue
struct CompareRank {
    bool operator()(const MusicObject& a, const MusicObject& b) {
        return a.rankScore < b.rankScore; //Maxheap higher rank comes first
    }
};

struct SongCollection {
    std::unordered_set<std::string> trackIDs;
    std::set<std::pair<std::string, std::string>> SongArtistNames; // exists exclusively to prevent duplicates
    std::priority_queue<MusicObject, std::vector<MusicObject>, CompareRank> queue;
};