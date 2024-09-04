#include "Word.h"

// Constructor
Word::Word(const std::string& name, const std::string& type, const std::string& definition)
    : name(name), type(type), definition(definition) {}

// Getters
std::string Word::getName() const { return name; }
std::string Word::getType() const { return type; }
std::string Word::getDefinition() const { return definition; }

// Setters
void Word::setName(const std::string& name) { this->name = name; }
void Word::setType(const std::string& type) { this->type = type; }
void Word::setDefinition(const std::string& definition) { this->definition = definition; }

// Print word definition
void Word::printDefinition() const {
    std::cout << "Word - " << name << "\nType - " << type << "\nDefinition - " << definition << "\n";
}

