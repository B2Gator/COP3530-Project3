#include "MusicObject.h"

//constructor
MusicObject::MusicObject(const std::string& artist, const std::string& song, const std::string& trackID, const std::string& genre,
                         float bpm, float valence, float energy, float instrumentalness)
    : ArtistName(artist), SongName(song), bpm(bpm), trackID(trackID), genre(genre), valence(valence), 
      energy(energy), instrumentalness(instrumentalness) {
   
    calculateMood();
    calculateHash();
    
}

//copy constructor
MusicObject::MusicObject(const MusicObject& other)
    : ArtistName(other.ArtistName),
    SongName(other.SongName),
    bpm(other.bpm),
    valence(other.valence),
    energy(other.energy),
    instrumentalness(other.instrumentalness),
    filterHash(other.filterHash),
    rankScore(other.rankScore),
    mood(other.mood),
    genre(other.genre),
    trackID(other.trackID) {}

//copy assignment operator

MusicObject& MusicObject::operator=(const MusicObject& other) {
    if (this != &other) {
        ArtistName = other.ArtistName;
        SongName = other.SongName;
        bpm = other.bpm;
        valence = other.valence;
        energy = other.energy;
        instrumentalness = other.instrumentalness;
        filterHash = other.filterHash;
        rankScore = other.rankScore;
        mood = other.mood;
        genre = other.genre;
        trackID = other.trackID;
    }
    return *this;
}


//move constructor

MusicObject::MusicObject(MusicObject&& other) noexcept
    : ArtistName(std::move(other.ArtistName)),
    SongName(std::move(other.SongName)),
    bpm(std::move(other.bpm)),
    valence(std::move(other.valence)),
    energy(std::move(other.energy)),
    instrumentalness(std::move(other.instrumentalness)),
    filterHash(std::move(other.filterHash)),
    rankScore(std::move(other.rankScore)),
    mood(std::move(other.mood)),
    genre(std::move(other.genre)),
    trackID(std::move(other.trackID)) {}

//move assignment operator

MusicObject& MusicObject::operator=(MusicObject&& other) noexcept {
    if (this != &other) {
        ArtistName = std::move(other.ArtistName);
        SongName = std::move(other.SongName);
        bpm = std::move(other.bpm);
        valence = std::move(other.valence);
        energy = std::move(other.energy);
        instrumentalness = std::move(other.instrumentalness);
        filterHash = std::move(other.filterHash);
        rankScore = std::move(other.rankScore);
        mood = std::move(other.mood);
        genre = std::move(other.genre);
        trackID = std::move(other.trackID);
    }
    return *this;
}

int MusicObject::calculateMood() {
	//Moods: 0 = happy, 1 = sad, 2 = angry, 3 = focused
    // all hash and mood values start at 0 to match with array/vector indices, otherwise you get subscript errors
    
	if (valence >= 0.5) { // valence is greater than half, either happy or focused
		if (energy < 0.5) {
			mood = 3; //focused
		}
		else // energy is > 0.5
			mood = 0; //happy
	}
	else { // valence is less than half, either sad or angry     
		if (energy < 0.5)
			mood = 1; // sad
		else
			mood = 2; // angry
	}

	return mood;
	

}

void MusicObject::calculateHash() {
    // all hash and mood values start at 0 to match with array/vector indices, otherwise you get subscript errors
	int bpmNum = 0;
        if (bpm < 150 && bpm >= 100) {
            bpmNum = 1;   //fast
        } else if (bpm < 100 && bpm >= 50) {
            bpmNum = 2;   //medium
        } else if (bpm < 50) {
            bpmNum = 3;  //slow
        } else {
            bpmNum = 0;  //very fast
        }

	int instrumentalnessNum = 0;
        if (instrumentalness < 0.2f) {
            instrumentalnessNum = 0;  // Mostly vocal
        } else if (instrumentalness < 0.5f) {
            instrumentalnessNum = 1;  // More vocal
        } else if (instrumentalness < 0.8f) {
            instrumentalnessNum = 2;  // More instrumental
        } else {
            instrumentalnessNum = 3;  // Mostly instrumental
        }


	filterHash = std::to_string(mood) + std::to_string(bpmNum) + std::to_string(instrumentalnessNum);
}



// each result is basically 1 - (actual value - ideal value)/ideal value
// A.K.A. "this value is this percent close to being the ideal"

float MusicObject::calculateMoodRank(int moodChoice) {
    float idealValenceForMood = idealValence[moodChoice];
    float idealEnergyForMood = idealEnergy[moodChoice];
    float moodResult = 1 - (std::abs(valence - idealValenceForMood) + std::abs(energy - idealEnergyForMood))/2;
    return moodResult;
}

float MusicObject::calculateTempoRank(int tempoChoice) {
    float idealTempoForChoice = idealTempo[tempoChoice];
    return 1 - std::abs(bpm - idealTempoForChoice)/idealTempoForChoice;
}

 float MusicObject::calculateInstrumentalnessRank(int instrumentalnessChoice) {
    float idealInstrumentalnessForChoice = idealInstrumentalness[instrumentalnessChoice];
    return 1 - std::abs(instrumentalness - idealInstrumentalnessForChoice);
}

void MusicObject::calculateRankScore(int moodChoice, int tempoChoice, int instrumentalnessChoice) {


    // std::cout << "Mood Rank: " << calculateMoodRank(moodChoice) << ", Tempo Rank: " << calculateTempoRank(tempoChoice)
    //     << ", Instrumentalness Rank: " << calculateInstrumentalnessRank(instrumentalnessChoice);


    // current idea for calculating ranks: default weight is 1/(number of factors, 3 in this case)
    rankScore = calculateMoodRank(moodChoice)/3 + calculateTempoRank(tempoChoice)/3 +
                calculateInstrumentalnessRank(instrumentalnessChoice)/3;


    //std::cout << ", Rank Score: " << rankScore << std::endl;

	
}