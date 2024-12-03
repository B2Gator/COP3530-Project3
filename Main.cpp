#include <iostream>
#include <chrono>
#include <limits>
#include "MusicDatabase.h"


int validatedInput(int min, int max) {
    int choice;
    while (true) {
        std::cin >> choice;
        if (std::cin.fail() || choice < min || choice > max) {
            std::cin.clear(); 
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Discard invalid input
            std::cout << "Invalid input. Please enter a number between " << min << " and " << max << ": ";
        } 
        else {
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Clear any extra input
            return choice;
        }
    }

}


int main() {

    std::string filename = "dataset.csv";
    MusicDB DB;

    int runAgain = 1;

    while(runAgain == 1){

        UserChoice input;

        //need to ensure valid inputs

        std::cout << "Welcome to the 'Song Generator'.\n";
        std::cout << "Please enter a 1, 2, 3, or 4 for each question";
        std::cout<<std::endl<<std::endl;

        std::cout << "What mood are you in?\n";
        std::cout << "1. Happy\n";
        std::cout << "2. Sad\n";
        std::cout << "3. Angry\n";
        std::cout << "4. Focused\n";
        std::cout << "Enter the number corresponding to your mood: ";
        //std::cin >> input.moodChoice;
        input.moodChoice = validatedInput(1,4);
        std::cout << std::endl;

        std::cout << "In terms of tempo, were you wanting..\n";
        std::cout << "1. Very fast\n";
        std::cout << "2. Fast\n";
        std::cout << "3. Medium\n";
        std::cout << "4. Slow\n";
        std::cout << "Enter the number corresponding to your tempo preference: ";
        //std::cin >> input.tempoChoice;
        input.tempoChoice = validatedInput(1,4);
        std::cout << std::endl;

        std::cout << "How about vocals/singing? Do you want..\n";
        std::cout << "1. Mainly vocals/singing\n";
        std::cout << "2. A moderate amount\n";
        std::cout << "3. Less vocals/singing\n";
        std::cout << "4. Little to none\n";
        std::cout << "Enter the number corresponding to your vocal preference: ";
        //std::cin >> input.instrumentalnessChoice;
        input.instrumentalnessChoice = validatedInput(1,4);
        std::cout << std::endl;



        std::string hashInput = std::to_string(input.moodChoice-1) + std::to_string(input.tempoChoice-1) + std::to_string(input.instrumentalnessChoice-1);
    

        int choice;

        std::cout << "Choose storage method" << std::endl;
        std::cout << "1 for Unordered Map or 2 for N-ary Tree: ";
        std::cin >> choice;
        std::cout << std::endl;

        bool infoResolution = false;
        char infoInput;

        std::cout << "Would you like to see additional info about your songs? (BPM, valence, energy, instrumentalness rank score)\n"
            << "Press 'y' or 'Y' for yes, anything else for no." << std::endl;
        std::cin >> infoInput;
        if (infoInput == 'y' || infoInput == 'Y') {
            infoResolution = true;
        }
        else infoResolution = false;

        auto t1 = std::chrono::high_resolution_clock::now();

        if (choice == 1){
            UnorderedMapStorage mapStorage;
            DB.processData(filename, input.moodChoice - 1, input.tempoChoice - 1, input.instrumentalnessChoice - 1, &mapStorage, nullptr, hashInput);
            mapStorage.displayTopSongs(hashInput, infoResolution);
            std::cout << std::endl;
        }
        
        else {

            NaryTreeStorage treeStorage;
            DB.processData(filename, input.moodChoice - 1, input.tempoChoice - 1, input.instrumentalnessChoice - 1, nullptr, &treeStorage, hashInput);
            treeStorage.displayTopSongs(hashInput, infoResolution);
            std::cout << std::endl;
        }

        auto t2 = std::chrono::high_resolution_clock::now();

        auto duration = std::chrono::duration_cast<std::chrono::microseconds>(t2 - t1);  
        std::cout << "Time taken: " << duration.count() / 1000000.0 << " seconds" << std::endl; //output time in seconds

        std::cout << std::endl;
        std::cout << "Enter 1 to run the program again or 0 to exit. ";
        std::cin >> runAgain;
        std::cout << std::endl;

    }
    
    std::cout << "Happy listening!";
    std::cout << std::endl;

    return 0;
}