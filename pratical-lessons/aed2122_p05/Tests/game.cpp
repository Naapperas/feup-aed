#include "game.h"
#include <cstdlib>
#include <ctime>
#include <iostream>
using namespace std;


unsigned int Game::numberOfWords(string phrase) {
  if ( phrase.length() == 0 ) return 0;

  unsigned n=1;
  size_t pos = phrase.find(' ');
  while (pos != string::npos) {
    phrase = phrase.substr(pos+1);
    pos = phrase.find(' ');
    n++;
  }
  return n;
}

Game::Game() {
	this->kids.clear();
}

Game::Game(list<Kid>& l2) {
	this->kids = l2;
}

//-----------------------------------------------------------------

// TODO
void Game::addKid(const Kid k1) {
    this->kids.push_back(k1);
}

// TODO
list<Kid> Game::getKids() const {
    return this->kids;
}

// TODO
void Game::setKids(const list<Kid>& l1) {
    this->kids = l1;
}

// TODO
Kid Game::loseGame(string phrase) {

    auto numWords = Game::numberOfWords(phrase) - 1;

    auto startIndex = 0;

    while (this->kids.size() > 1) {

        startIndex = (startIndex + numWords) % this->kids.size();

        auto kid = this->kids.begin();

        auto tmp = 0;
        while (tmp++ < startIndex) ++kid;

        this->kids.erase(kid);
    }

    return this->kids.back();
}

// TODO
list<Kid> Game::removeOlder(unsigned id) {

    list<Kid> result;

    auto it = this->kids.begin();

    while (it != this->kids.end()) {
        if (it->getAge() > id) {
            result.push_back(*it);
            it = this->kids.erase(it);
        } else
            it++;
    }

    return result;
}

// TODO
queue<Kid> Game::rearrange() {

    list<Kid> male, female;

    queue<Kid> ret;

    for (const auto& kid : this->kids)
        (kid.getSex() == 'm' ? male : female).push_back(kid);

    this->kids.clear();

    short pattern;
    if (female.size() < male.size()) {

        pattern = male.size() / female.size();

        while (female.size() > 0) {

            auto f = *(female.begin());
            female.pop_front();
            this->kids.push_back(f);

            for (int i = 0; i < pattern; ++i) {
                auto m = *(male.begin());
                male.pop_front();
                this->kids.push_back(m);
            }
        }

        for (const auto& kid : male) ret.push(kid);

    } else {

        pattern = female.size() / male.size();

        while (male.size() > 0) {

            auto m = *(male.begin());
            male.pop_front();
            this->kids.push_back(m);

            for (int i = 0; i < pattern; ++i) {
                auto f = *(female.begin());
                female.pop_front();
                this->kids.push_back(f);
            }
        }

        for (const auto& kid : female) ret.push(kid);

    }

    return ret;
}

// TODO
bool Game::operator==(Game& g2) {
	return this->kids == g2.kids;
}

// TODO
list<Kid> Game::shuffle() const {
    list<Kid> kids{this->kids};
    list<Kid> l{};

    while (!kids.empty()) {
        int n = rand() % kids.size();
        auto k{kids.begin()};
        for (int i{0}; i < n; ++i, ++k)
            ;
        l.push_back(*k);
        kids.erase(k);
    }

    return l;
}
