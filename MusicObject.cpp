#include "MusicObject.h"

//constructor
MusicObject::MusicObject(const std::string& artist, const std::string& song, 
                         float bpm, float valence, float energy, float instrumentalness)
    : ArtistName(artist), SongName(song), bpm(bpm), valence(valence), 
      energy(energy), instrumentalness(instrumentalness) {
   
    calculateMood();
    calculateHash();
    
}

int MusicObject::calculateMood() {
	//Moods: 1=happy, 2=sad, 3=chill, 4=angry  //maybe make this 1,2,3,4 to correspond to user input??
    
	if (valence >= 0.5) { // valence is greater than half, either happy or chill
		if (energy < 0.5) {
			mood = 3;
		}
		else // energy is > 0.5
			mood = 1;
	}
	else { // valence is less than half, either sad or angry     
		if (energy < 0.5)
			mood = 2; // sad
		else;
			mood = 4; // angry
	}

	return mood;
	
}

void MusicObject::calculateHash() {

	int bpmNum = 0;
        if (bpm < 50) {
            bpmNum = 4;  
        } else if (bpm < 100) {
            bpmNum = 3;
        } else if (bpm < 150) {
            bpmNum = 2;  
        } else {
            bpmNum = 1;  
        }

	int instrumentalnessNum = 0;
        if (instrumentalness < 0.2f) {
            instrumentalnessNum = 1;  // Mostly vocal
        } else if (instrumentalness < 0.5f) {
            instrumentalnessNum = 2;  // Moderate vocals
        } else if (instrumentalness < 0.8f) {
            instrumentalnessNum = 3;  // Less vocals
        } else {
            instrumentalnessNum = 4;  // Mostly instrumental
        }


	filterHash = std::to_string(mood) + std::to_string(bpmNum) + std::to_string(instrumentalnessNum);
}


float MusicObject::calculateMoodRank(int moodChoice) {
    float idealValenceForMood = idealValence[moodChoice];
    float idealEnergyForMood = idealEnergy[moodChoice];
    return -(std::abs(valence-idealValenceForMood) + std::abs(energy-idealEnergyForMood));
}

float MusicObject::calculateTempoRank(int tempoChoice) {
    float idealTempoForChoice = idealTempo[tempoChoice];
    return -std::abs(bpm - idealTempoForChoice);
}

 float MusicObject::calculateInstrumentalnessRank(int instrumentalnessChoice) {
    float idealInstrumentalnessForChoice = idealInstrumentalness[instrumentalnessChoice];
    return -std::abs(instrumentalness - idealInstrumentalnessForChoice);
}

void MusicObject::calculateRankScore(int moodChoice, int tempoChoice, int instrumentalnessChoice) {

    std::cout << "Mood Rank: " << calculateMoodRank(moodChoice) << ", Tempo Rank: " << calculateTempoRank(tempoChoice)
              << ", Instrumentalness Rank: " << calculateInstrumentalnessRank(instrumentalnessChoice) << std::endl;

    rankScore = calculateMoodRank(moodChoice) + calculateTempoRank(tempoChoice) +
                calculateInstrumentalnessRank(instrumentalnessChoice);
	
}