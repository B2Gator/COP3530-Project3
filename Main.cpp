#include <iostream>
#include "ParsingCSV.h"


int main() {

    std::string filename = "dataset.csv";

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
    std::cin >> input.moodChoice;
    std::cout << std::endl;

    std::cout << "In terms of tempo, were you wanting..\n";
    std::cout << "1. Very fast\n";
    std::cout << "2. Fast\n";
    std::cout << "3. Medium\n";
    std::cout << "4. Slow\n";
    std::cout << "Enter the number corresponding to your tempo preference: ";
    std::cin >> input.tempoChoice;
    std::cout << std::endl;

    std::cout << "How about vocals/singing? Do you want..\n";
    std::cout << "1. Mainly vocals/singing\n";
    std::cout << "2. A moderate amount\n";
    std::cout << "3. Less vocals/singing\n";
    std::cout << "4. Little to none\n";
    std::cout << "Enter the number corresponding to your vocal preference: ";
    std::cin >> input.instrumentalnessChoice;
    std::cout << std::endl;

    std::string userHash = std::to_string(input.moodChoice) + std::to_string(input.tempoChoice) + std::to_string(input.instrumentalnessChoice);
    int choice;

    std::cout << "Choose storage method" << std::endl;
    std::cout << "1 for Unordered Map or 2 for N-ary Tree: ";
    std::cin >> choice;
    std::cout << std::endl;

    //processData(filename, input.moodChoice, input.tempoChoice, input.instrumentalnessChoice);

    if (choice == 1){
        UnorderedMapStorage mapStorage;
        processData(filename, input.moodChoice, input.tempoChoice, input.instrumentalnessChoice, &mapStorage, nullptr, userHash);
        mapStorage.displayTopSongs(userHash);
    }
    
    else if(choice == 2){

        std::cout << "Implement n-ary tree" << std::endl;
        // UnorderedMapStorage treeStorage;
        // processData(filename, input.moodChoice, input.tempoChoice, input.instrumentalnessChoice, nullptr, &treeStorage, userHash);

    }

    
    return 0;
}