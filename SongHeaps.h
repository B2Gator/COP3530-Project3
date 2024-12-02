#pragma once
#include <set>
#include <queue>
#include "MusicObject.h"


//comparator for the max-heap priority queue
struct CompareRank {
    bool operator()(const MusicObject& a, const MusicObject& b) {
        return a.rankScore < b.rankScore; //Maxheap higher rank comes first
    }
};

struct SongCollection {
    std::set<std::string> trackIDs;
    std::priority_queue<MusicObject, std::vector<MusicObject>, CompareRank> queue;
};