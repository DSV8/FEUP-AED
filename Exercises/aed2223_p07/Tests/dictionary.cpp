#include <iostream>
#include <string>
#include <fstream>
#include "dictionary.h"

using namespace std;

WordMean::WordMean(string w, string m): word(w), meaning(m) {}

string WordMean::getWord() const {return word;}
string WordMean::getMeaning() const {return meaning;}

void WordMean::setMeaning(string m) {meaning = m;}
void WordMean::setWord(string w) {word = w;}

set<WordMean> Dictionary::getWords() const {return words;}

void Dictionary::addWord(WordMean wm)  {words.insert(wm);}

// ---------------------------------------------

//TODO
bool WordMean::operator< (const WordMean& wm2) const {return word < wm2.getWord();}


//TODO
void Dictionary::readFile(ifstream &f) {
    for (string wrd, mean; getline(f, wrd), getline(f, mean);){
        addWord(WordMean(wrd, mean));
    }
}

//TODO
string Dictionary::consult(string w1, WordMean& previous, WordMean& next) const {
    for (auto it = words.begin(); it != words.end(); it++){
        if (it->getWord() > w1) {next = *it; break;}
        else if (it->getWord() == w1) {return it->getMeaning();}
        previous = *it;
    }

    return "word not found";
}

//TODO
bool Dictionary::update(string w1, string m1) {
    bool isIn = false;

    for (auto it = words.begin(); it != words.end(); it++){
        if (it->getWord() == w1) {words.erase(it); isIn = true;}
    }
    addWord(WordMean(w1, m1));
    return isIn;
}

//TODO
void Dictionary::print() const {
    for (auto wm : words){
        cout << wm.getWord() << "\n" << wm.getMeaning() << endl;
    }
}
