// AED 2021/2022 - Aula Pratica 07
// Pedro Ribeiro (DCC/FCUP) [06/12/2021]

#include <set>
#include <map>
#include <algorithm>
#include "funWithBSTs.h"
#include "bst.h"

// ----------------------------------------------------------
// Exercicio 1: Colecao de Cromos
// ----------------------------------------------------------
// TODO
int FunWithBSTs::newBag(const vector<int>& collection, const vector<int>& bag) {

  int result = 0;

  set<int> coll{collection.begin(), collection.end()};

  int previousSize = coll.size();

  for (auto elem : bag) {
    coll.insert(elem);
    if (coll.size() != previousSize) {
      previousSize = coll.size();
      result++;
    }
  }
  
  return result;
}

// ----------------------------------------------------------
// Exercicio 2: Batalha de Pokemons
// ----------------------------------------------------------
// TODO
int FunWithBSTs::battle(const vector<int>& alice, const vector<int>& bruno) {

  // not possible with BST class since it removes duplicates

  multiset<int> aliceSet, brunoSet;

  aliceSet.insert(alice.begin(), alice.end());
  brunoSet.insert(bruno.begin(), bruno.end());

  while (aliceSet.size() * brunoSet.size() > 0) {

    auto aliceChosenCard = --aliceSet.end(); // since these are BSTs, the rightmost element (thus the last de-referencable iterator) will have the highest value
    auto brunoChosenCard = --brunoSet.end(); // since these are BSTs, the rightmost element (thus the last de-referencable iterator) will have the highest value

    int aliceCard = *aliceChosenCard;
    int brunoCard = *brunoChosenCard;

    aliceSet.erase(aliceChosenCard);
    brunoSet.erase(brunoChosenCard);

    if (aliceCard > brunoCard)
      aliceSet.insert(aliceCard - brunoCard);
    else if (aliceCard < brunoCard)
      brunoSet.insert(brunoCard - aliceCard);
  }

  /*
    if there is a tie, both sets will have the same size so it will return 0
    if alice won, it will return a positive number
    if bruno won, it will return a negative number
   */
  return aliceSet.size() - brunoSet.size();
}

// ----------------------------------------------------------
// Exercicio 3: Reviews Cinematograficas
// ----------------------------------------------------------

// ..............................
// a) Contando Filmes
// TODO
int FunWithBSTs::numberMovies(const vector<pair<string, int>>& reviews) {
  return map<string, int>(reviews.begin(), reviews.end()).size();
}

// ..............................
// b) O filme com mais reviews
// TODO
void FunWithBSTs::moreReviews(const vector<pair<string, int>>& reviews, int& m, int& n) {

  map<string, int> rev;

  for (auto pair : reviews)
    rev.insert({pair.first, 0});

  for (auto pair : reviews)
    rev[pair.first]++;
  
  m = 0;
  for (auto pair : rev)
    if (pair.second > m)
      m = pair.second;

  n = 0;
  for (auto pair : rev)
    if (pair.second == m)
      n++;
}

// ..............................
// c) Os melhores filmes
// TODO
vector<string> FunWithBSTs::topMovies(const vector<pair<string, int>>& reviews, double k) {
  vector<string> answer;

  map<string, int> numReviews;
  map<string, double> scores;

  for (auto pair : reviews) {
    auto& reviewCount = numReviews[pair.first];
    auto& oldAverageScore = scores[pair.first];

    double score = reviewCount*oldAverageScore;

    score += pair.second;
    reviewCount++;

    oldAverageScore = score/reviewCount;
  }

  for (auto pair : scores) {
    if (pair.second >= k)
        answer.push_back(pair.first);
  }

  return answer;
}
