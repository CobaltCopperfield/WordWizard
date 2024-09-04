#ifndef IMPROVEDDICTIONARY_H
#define IMPROVEDDICTIONARY_H

#include "Dictionary.h"

/**
 * Class: ImprovedDictionary
 * ----------------------------
 * Extends the Dictionary class to add additional functionality like guessing a word
 * and other enhanced features.
 */

class ImprovedDictionary : public Dictionary {
public:
    void showMenu() override;

private:
    void guessFourthWord();
    int loadHighestScore();
    void saveHighestScore(int score);
};

#endif // IMPROVEDDICTIONARY_H

