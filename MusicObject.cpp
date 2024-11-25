#include "MusicObject.h"


MusicObject::MusicObject(const std::string& artist, const std::string& song, 
                         float bpm, float valence, float energy, float instrumentalness)
    : ArtistName(artist), SongName(song), bpm(bpm), valence(valence), 
      energy(energy), instrumentalness(instrumentalness) {
    // Calculate the hash or mood right after constructing the object if needed
    calculateHash();
}

int MusicObject::calculateMood() {
	//Moods: 0=happy, 1=sad, 2=chill, 3=angry  //maybe make this 1,2,3,4 to correspond to user input??
    int mood;
	if (valence >= 0.5) { // valence is greater than half, either happy or chill
		if (energy < 0.5) {
			mood = 2;
		}
		else // energy is > 0.5
			mood = 0;
	}
	else { // valence is less than half, either sad or angry     
		if (energy < 0.5)
			mood = 1; // sad
		else;
			mood = 3; // angry
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



// int MusicObject::SongMood(int valence, int energy) {
// 	int moodVal = 0; //Moods: 0=happy, 1=sad, 2=chill, 3=angry  //maybe make this 1,2,3,4 to correspond to user input??
    
// 	if (valence >= 0.5) { // valence is greater than half, either happy or chill
// 		if (energy < 0.5) {
// 			moodVal = 2;
// 		}
// 		else // energy is > 0.5
// 			moodVal = 0;
// 	}
// 	else { // valence is less than half, either sad or angry     
// 		if (energy < 0.5)
// 			moodVal = 1; // sad
// 		else;
// 			moodVal = 3; // angry
// 	}
	
// 	return moodVal;
// }


