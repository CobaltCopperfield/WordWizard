#include "Dictionary.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <algorithm>
#include <cctype>

// Helper function to remove leading and trailing whitespace
inline std::string removeWhitespace(const std::string& str) {
    size_t start = str.find_first_not_of(" \t\n\r\f\v");
    size_t end = str.find_last_not_of(" \t\n\r\f\v");
    return (start == std::string::npos) ? "" : str.substr(start, end - start + 1);
}

// Helper function to convert a string to lowercase
inline std::string toLowerCase(const std::string& str) {
    std::string lowerStr = str;
    std::transform(lowerStr.begin(), lowerStr.end(), lowerStr.begin(), ::tolower);
    return lowerStr;
}

// Helper function to check if a string contains only alphabetic characters and hyphens
inline bool isValidWord(const std::string& str) {
    return std::all_of(str.begin(), str.end(), [](char c) {
        return std::isalpha(c) || c == '-';
    });
}

// Load dictionary from a file
bool Dictionary::loadFromFile(const std::string& fileName) {
    std::ifstream file(fileName);
    if (!file.is_open()) {
        std::cerr << "File not found: " << fileName << ". Loading default file: dictionary01.txt\n";
        file.open("dictionary01.txt");
        if (!file.is_open()) {
            std::cerr << "Error: Default file 'dictionary01.txt' could not be opened either.\n";
            return false;
        }
    }

    std::string line;
    Word word;

    // Read the file line by line
    while (getline(file, line)) {
        line = removeWhitespace(line);  // Remove leading and trailing whitespace

        if (line.find("Type: ") == 0) {
            word.setType(removeWhitespace(line.substr(6)));
        } else if (line.find("Definition: ") == 0) {
            word.setDefinition(removeWhitespace(line.substr(12)));
        } else if (line.find("Word: ") == 0) {
            std::string rawWord = line.substr(6);
            std::string trimmedWord = toLowerCase(removeWhitespace(rawWord)); // Convert to lowercase
            word.setName(trimmedWord);

            // Add the word to the dictionary once all fields are populated
            if (!word.getName().empty()) {
                wordMap[word.getName()] = word;
            }

            // Reset the word object for the next entry
            word = Word();
        }
    }

    file.close();
    if (wordMap.empty()) {
        std::cerr << "Error: Dictionary could not be loaded. The file might be empty or improperly formatted.\n";
        return false;
    }

    std::cout << "Dictionary loaded successfully!\n";
    return true;
}

// Search for a word in the dictionary
void Dictionary::searchWord(const std::string& word) const {
    std::string trimmedWord = toLowerCase(removeWhitespace(word)); // Convert to lowercase
    if (trimmedWord.empty() || !isValidWord(trimmedWord)) {
        std::cerr << "Invalid input: Please enter a valid word containing only alphabetic characters or hyphens.\n";
        return;
    }

    auto it = wordMap.find(trimmedWord);
    if (it != wordMap.end()) {
        it->second.printDefinition();
    } else {
        std::cout << "Word not found.\n";
    }
}

// Add a new word to the dictionary and save the dictionary to a file
void Dictionary::addWord(const Word& word) {
    std::string trimmedName = toLowerCase(removeWhitespace(word.getName())); // Convert to lowercase

    if (trimmedName.empty() || !isValidWord(trimmedName)) {
        std::cerr << "Invalid word name: Please enter a valid word containing only alphabetic characters or hyphens.\n";
        return;
    }

    if (word.getType().empty() || word.getDefinition().empty()) {
        std::cerr << "Invalid input: Type and definition cannot be empty.\n";
        return;
    }

    if (wordMap.find(trimmedName) != wordMap.end()) {
        std::cout << "Error: Word already exists, elevated privileges required to edit existing words.\n";
        return;
    }

    wordMap[trimmedName] = word;
    std::cout << "Word added successfully!\n";

    // Ask the user whether to overwrite the existing file or save to a new file
    std::string saveChoice;
    std::cout << "Do you want to overwrite the existing file or save to a new file? (o/n): ";
    std::getline(std::cin, saveChoice);

    if (toLowerCase(saveChoice) == "o") {
        saveToFile("dictionary01.txt");
    } else {
        std::string newFileName;
        std::cout << "Enter the new file name to save: ";
        std::getline(std::cin, newFileName);
        saveToFile(newFileName);
    }
}

// Save the dictionary to a file
bool Dictionary::saveToFile(const std::string& fileName) const {
    if (fileName.empty()) {
        std::cerr << "Invalid file name: File name cannot be empty.\n";
        return false;
    }

    std::ofstream file(fileName);
    if (!file.is_open()) {
        std::cerr << "Error: Could not open file for writing.\n";
        return false;
    }

    for (const auto& pair : wordMap) {
        const Word& word = pair.second;
        file << "Type: " << word.getType() << "\n"
             << "Definition: " << word.getDefinition() << "\n"
             << "Word: " << word.getName() << "\n\n";
    }

    file.close();
    std::cout << "Dictionary saved successfully to " << fileName << "\n";
    return true;
}

// Display the main menu
void Dictionary::showMenu() {
    while (true) {
        std::cout << "\n----- The Main Menu -----\n"
                  << "1. Search Word In The Dictionary\n"
                  << "2. Add a Word to the Dictionary\n"
                  << "3. Save Dictionary\n"
                  << "4. Quit\n"
                  << "Enter Number: ";

        std::string choice;
        std::cin >> choice;
        std::cin.ignore();  // Discard the newline character after input

        if (choice == "1") {
            std::string word;
            std::cout << "\nEnter the word to search: ";
            std::getline(std::cin, word);
            searchWord(word);
        } else if (choice == "2") {
            std::string name, type, definition;
            std::cout << "\nEnter the word name: ";
            std::getline(std::cin, name);
            std::cout << "Enter the word type: ";
            std::getline(std::cin, type);
            std::cout << "Enter the word definition: ";
            std::getline(std::cin, definition);
            addWord(Word(name, type, definition));
        } else if (choice == "3") {
            std::string fileName;
            std::cout << "\nEnter the file name to save: ";
            std::getline(std::cin, fileName);
            saveToFile(fileName);
        } else if (choice == "4") {
            std::cout << "Exiting program.\n";
            break;
        } else {
            std::cerr << "Invalid choice. Please enter a number between 1 and 4.\n";
        }
    }
}

