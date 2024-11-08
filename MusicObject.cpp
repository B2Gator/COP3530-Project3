#include <MusicObject.h>

int MusicObject::SongMood(int valence, int energy) {
	int moodVal = 0; //Moods: 0=happy, 1=sad, 2=chill, 3=angry
    
	if (valence >= 0.5) { // valence is greater than half, either happy or chill
		if (energy < 0.5) {
			moodVal = 2;
		}
		else // energy is > 0.5
			moodVal = 0;
	}
	else { // valence is less than half, either sad or angry     
		if (energy < 0.5)
			moodVal = 1; // sad
		else;
			moodVal = 3; // angry
	}
	
	return moodVal;
}


