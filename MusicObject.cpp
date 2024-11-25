#include "MusicObject.h"

//constructor
MusicObject::MusicObject(const std::string& artist, const std::string& song, 
                         float bpm, float valence, float energy, float instrumentalness)
    : ArtistName(artist), SongName(song), bpm(bpm), valence(valence), 
      energy(energy), instrumentalness(instrumentalness) {
   
    calculateHash();
}

int MusicObject::calculateMood() {
	//Moods: 1=happy, 2=sad, 3=chill, 4=angry  //maybe make this 1,2,3,4 to correspond to user input??
    int mood;
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

	int moodNum = calculateMood();

	int bpmNum = 0;
        if (bpm < 50) {
            bpmNum = 3;  
        } else if (bpm < 100) {
            bpmNum = 2;
        } else if (bpm < 150) {
            bpmNum = 1;  
        } else {
            bpmNum = 0;  
        }

	int instrumentalnessNum = 0;
        if (instrumentalness < 0.2f) {
            instrumentalnessNum = 0;  // Mostly vocal
        } else if (instrumentalness < 0.5f) {
            instrumentalnessNum = 1;  // Moderate vocals
        } else if (instrumentalness < 0.8f) {
            instrumentalnessNum = 2;  // Less vocals
        } else {
            instrumentalnessNum = 3;  // Mostly instrumental
        }


	filterHash = std::to_string(moodNum) + std::to_string(bpmNum) + std::to_string(instrumentalnessNum);
}

