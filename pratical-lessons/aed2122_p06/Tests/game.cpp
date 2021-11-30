#include "game.h"
#include <sstream>
#include <cmath>

Circle::Circle(int p, bool s): points(p), state(s), nVisits(0) {}

int Circle::getPoints() const {
    return points;
}

bool Circle::getState() const {
    return state;
}

void Circle::changeState() {
    state = !state;
}

int Circle::getNVisits() const {
    return nVisits;
}

void Circle::incNVisits() {
    nVisits++;
}


BinaryTree<Circle>& Game::getGame() {
    return game;
}


//-----------------------------------------------------------------

//TODO
Game::Game(int height, vector<int>& points, vector<bool>& states) {

    vector<BinaryTree<Circle>*> nodes(points.size(), NULL);

    for (int i = points.size() - 1; i >= 0; --i) {
        if (i >= std::pow(2, height)-1)
            nodes.at(i) = new BinaryTree<Circle>({points.at(i), states.at(i)});
        else
            nodes.at(i) = new BinaryTree<Circle>({points.at(i), states.at(i)}, *nodes.at(2*i+1), *nodes.at(2*i+2));
    }

    this->game = *(nodes.at(0));
}

//TODO
int Game::play() {

    auto node = this->game.root;

    int score = 0;

    while (node != NULL) {
        node->element.incNVisits();

        score = node->element.getPoints();

        if (node->element.getState()) {
            node->element.changeState();
            node = node->right;
        } else {
            node->element.changeState();
            node = node->left;
        }
    }

	return score;
}

//TODO
int Game::mostVisited() const {

    int max = INT32_MIN;

    BTItrPre<Circle> itr(this->game);

    while (!itr.isAtEnd()) {
        if (itr.retrieve().getPoints() != 1 && itr.retrieve().getNVisits() > max) max = itr.retrieve().getNVisits();
        itr.advance();
    }

	return max;
}

