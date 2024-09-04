#ifndef WORD_H
#define WORD_H

#include <string>
#include <iostream>

/**
 * Class: Word
 * ----------------------------
 * Represents a word in the dictionary, containing its name, type, and definition.
 */
 
class Word {
private:
    std::string name;
    std::string type;
    std::string definition;

public:
    // Constructor
    Word(const std::string& name = "", const std::string& type = "", const std::string& definition = "");

    // Getters
    std::string getName() const;
    std::string getType() const;
    std::string getDefinition() const;

    // Setters
    void setName(const std::string& name);
    void setType(const std::string& type);
    void setDefinition(const std::string& definition);

    // Print word definition
    void printDefinition() const;
};

#endif // WORD_H

