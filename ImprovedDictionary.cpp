#include "ImprovedDictionary.h"
#include <random>   // For random number generation
#include <fstream>  // For file operations
#include <iostream>
#include <sstream>

// Helper function to remove leading and trailing whitespace
inline std::string removeWhitespace(const std::string& str) {
    size_t start = str.find_first_not_of(' ');
    size_t end = str.find_last_not_of(' ');
    return (start == std::string::npos) ? "" : str.substr(start, end - start + 1);
}

// Load the highest score from a file
int ImprovedDictionary::loadHighestScore() {
    int highestScore = 0;
    std::ifstream scoreFile("highest_score.txt");
    if (scoreFile.is_open()) {
        scoreFile >> highestScore;
        scoreFile.close();
    }
    return highestScore;
}

// Save the highest score to a file
void ImprovedDictionary::saveHighestScore(int score) {
    std::ofstream scoreFile("highest_score.txt");
    if (scoreFile.is_open()) {
        scoreFile << score;
        scoreFile.close();
    }
}

void ImprovedDictionary::guessFourthWord() {
    std::random_device rd;
    std::mt19937 gen(rd());  // Mersenne Twister engine
    int score = 0;
    int highestScore = loadHighestScore();

    std::cout << "\n-- Welcome to 'Guess the Fourth Word'! --\n";
    std::cout << "Current High Score: " << highestScore << "\n";

    while (true) {
        std::ifstream dictFile("dictionary01.txt");
        if (!dictFile.is_open()) {
            std::cerr << "Error: Could not open the dictionary file.\n";
            return;
        }

        std::vector<Word> eligibleWords;
        std::string line;
        Word currentWord;

        // Process the dictionary file line by line
        while (std::getline(dictFile, line)) {
            line = removeWhitespace(line);  // Remove leading and trailing whitespace

            if (line.find("Type: ") == 0) {
                currentWord.setType(removeWhitespace(line.substr(6)));
            } else if (line.find("Definition: ") == 0) {
                currentWord.setDefinition(removeWhitespace(line.substr(12)));
            } else if (line.find("Word: ") == 0) {
                currentWord.setName(removeWhitespace(line.substr(6)));

                // Check if the definition has more than 4 words
                std::istringstream stream(currentWord.getDefinition());
                std::vector<std::string> definitionWords;
                std::string tempWord;
                while (stream >> tempWord) {
                    definitionWords.push_back(tempWord);
                    if (definitionWords.size() > 4) {
                        eligibleWords.push_back(currentWord);
                        break;
                    }
                }

                // Reset the word object for the next entry
                currentWord = Word();
            }
        }

        dictFile.close();

        // Check if we have any eligible words
        if (eligibleWords.empty()) {
            std::cout << "No eligible words with more than 4 words in their definition were found.\n";
            return;
        }

        // Generate a uniform distribution over the range of eligible words
        std::uniform_int_distribution<> dist(0, eligibleWords.size() - 1);

        // Choose a random word from the eligible words
        int randomIndex = dist(gen);
        Word randomWord = eligibleWords[randomIndex];

        // Tokenize the chosen word's definition
        std::istringstream stream(randomWord.getDefinition());
        std::vector<std::string> definitionWords;
        std::string word;
        while (stream >> word) {
            definitionWords.push_back(word);
        }

        // Replace the fourth word with underscores
        std::string correctWord = definitionWords[3];
        definitionWords[3] = std::string(correctWord.size(), '_');

        // Print the randomly selected word and the modified definition
        std::cout << "Instructions: Guess the missing word in definition.\n";
        std::cout << "\nSelected word: " << randomWord.getName() << "\n";
        std::cout << "Definition: ";
        for (const auto& w : definitionWords) {
            std::cout << w << " ";
        }
        std::cout << "\nYour guess: ";

        std::string guess;
        std::getline(std::cin, guess);

        // Check if the user's guess is correct
        if (guess == correctWord) {
            std::cout << "Congratulations! You guessed correctly.\n";
            score += 10;

            // Continue to the next round
            std::cout << "Your current score is: " << score << "\n";

        } else {
            std::cout << "Incorrect. The correct word was: " << correctWord << "\n";
            std::cout << "Your final score is: " << score << "\n";
            break;
        }
    }

    // Update and save the highest score if necessary
    if (score > highestScore) {
        std::cout << "New High Score! You've beaten the previous high score.\n";
        saveHighestScore(score);
    }
}

void ImprovedDictionary::showMenu() {
    while (true) {
        std::cout << "\n----- The Main Menu -----\n"
                  << "1. Search Word In The Dictionary\n"
                  << "2. Add a Word to the Dictionary\n"
                  << "3. Save Dictionary\n"
                  << "4. Guess the Fourth Word\n"
                  << "5. Quit\n"
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
            guessFourthWord();
        } else if (choice == "5") {
            std::cout << "Exiting program.\n";
            break;
        } else {
            std::cout << "Invalid choice. Please enter a number between 1 and 5.\n";
        }
    }
}

