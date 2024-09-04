#include "ImprovedDictionary.h"
#include <iostream>

/**
 * Function: main
 * ----------------------------
 * The main function initializes the ImprovedDictionary, loads the dictionary from a file,
 * and then displays the menu for the user to interact with the dictionary.
 */
 
int main() {
    ImprovedDictionary dictionary;

    // Prompt the user for the file name and attempt to load the dictionary
    std::string fileName;
    std::cout << "Enter the dictionary file name: ";
    std::getline(std::cin, fileName);

    // Attempt to load the dictionary, exit if unsuccessful
    if (!dictionary.loadFromFile(fileName)) {
        return 1;  // Exit if the dictionary could not be loaded
    }

    // Display the main menu
    dictionary.showMenu();

    return 0;
}

