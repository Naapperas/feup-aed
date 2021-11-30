#include <iostream>
#include <string>
#include <fstream>
#include "dictionary.h"

using namespace std;

WordMean::WordMean(string w, string m): word(w), meaning(m) {}

string WordMean::getWord() const {
    return word;
}

string WordMean::getMeaning() const {
    return meaning;
}

void WordMean::setMeaning(string m) {
    meaning = m;
}

void WordMean::setWord(string w) {
    word = w;
}

BST<WordMean> Dictionary::getWords() const {
	return words;
}

bool operator< (const WordMean& a, const WordMean& b) {
    return a.getWord() < b.getWord();
}

ostream& operator<<(ostream& out, const WordMean& b) {
    out << b.word << '\n' << b.meaning << '\n';
    return out;
}

// ---------------------------------------------

//TODO
void Dictionary::readFile(ifstream &f) {

    // ifstream is already opened

    string w, m;
    while(std::getline(f, w) && std::getline(f, m)) {

        if (w.at(w.size()-1) == '\r')
            w.pop_back();

        if (m.at(m.size()-1) == '\r')
            m.pop_back();

        this->words.insert(WordMean(w, m));
    }
}

//TODO
string Dictionary::consult(string word1, WordMean& previous, WordMean& next) const {

    for (auto itr = this->words.begin(); itr != this->words.end(); itr++) {

        if ((*itr).getWord() == word1) return (*itr).getMeaning();
        else if ((*itr).getWord() > word1) {
            next = *itr;
            return "word not found";
        } else
            previous = *itr; // we are always setting the previous element here, so if we reach an element after the word given, previous is already set, and we only have to car about next
    }
}

//TODO
bool Dictionary::update(string word1, string mean1) {

    for (auto itr = this->words.begin(); itr != this->words.end(); itr++) {
        if ((*itr).getWord() == word1) {
            auto obj = *itr;
            this->words.remove(obj);
            obj.setMeaning(mean1);
            this->words.insert(obj);
            return true;
        }
    }

    this->words.insert({word1, mean1});
    return false;
}

//TODO
void Dictionary::print() const {
    this->words.printTree();
}
