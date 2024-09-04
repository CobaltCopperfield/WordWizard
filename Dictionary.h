#ifndef DICTIONARY_H
#define DICTIONARY_H

#include "Word.h"
#include <map>
#include <string>

/**
 * Class: Dictionary
 * ----------------------------
 * Manages a collection of Word objects, including loading from a file, searching,
 * adding words, and saving to a file.
 */

class Dictionary {
protected:
    std::map<std::string, Word> wordMap;

public:
    // Load dictionary from a file
    bool loadFromFile(const std::string& fileName);

    // Search for a word in the dictionary
    void searchWord(const std::string& word) const;

    // Add a new word to the dictionary
    void addWord(const Word& word);

    // Save the dictionary to a file
    bool saveToFile(const std::string& fileName) const;

    // Display the main menu
    virtual void showMenu();
};

#endif // DICTIONARY_H

