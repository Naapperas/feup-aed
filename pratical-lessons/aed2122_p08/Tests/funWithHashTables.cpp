// AED 2021/2022 - Aula Pratica 08
// Pedro Ribeiro (DCC/FCUP) [12/12/2021]

#include "funWithHashTables.h"
#include "hashTable.h"

#include <vector>
#include <iostream>
#include <cctype>

// Exemplo de função de hash para ints
unsigned FunWithHashTables::hashInt(const int &i)
{
  return i;
}

// Exemplo de função de hash para strings
unsigned FunWithHashTables::hashString(const string &s)
{
  hash<string> h;
  return h(s);
}

// ----------------------------------------------------------
// Exercicio 1: Tabelas de Dispersão
// ----------------------------------------------------------

// ..............................
// d) Contando diferentes somas de pares
// TODO
int FunWithHashTables::sumPairs(const vector<int> &numbers)
{

  HashTable<int> table(numbers.size() * numbers.size(), hashInt);

  for (unsigned i = 0; i < numbers.size(); i++)
    for (unsigned j = i + 1; j < numbers.size(); j++)
      table.insert(numbers[i] + numbers[j]);

  return table.getNumActive();
}

// ----------------------------------------------------------
// Exercicio 2: Um padrão no DNA
// ----------------------------------------------------------
// TODO
int FunWithHashTables::dnaMotifs(string dna, int k, unordered_set<string> &motifs)
{

  unordered_map<string, int> frequencies;

  int biggestFreq = 0;

  for (unsigned i = 0, freq = 0; i < dna.size() - k + 1; i++)
    if ((freq = ++frequencies[dna.substr(i, k)]) > biggestFreq)
      biggestFreq = freq;

  motifs.clear();
  for (const auto &[motif, freq] : frequencies)
    if (freq == biggestFreq)
      motifs.insert(motif);

  return biggestFreq;
}

vector<string> split(string &text)
{
  vector<string> result;

  transform(text.begin(), text.end(), text.begin(), [](unsigned char c)
            { return tolower(c); });

  string tmp;
  for (char c : text)
    if (isalpha(c))
      tmp += c;
    else if (tmp != "")
    {
      result.push_back(tmp);
      tmp = "";
    }

  result.push_back(tmp);
  return result;
}

// ----------------------------------------------------------
// Exercicio 3: Torre de Babel
// ----------------------------------------------------------
// TODO
void FunWithHashTables::findLanguage(string text, const unordered_map<string, vector<string>> &dict, unordered_map<string, int> &answer)
{

  auto tokens = split(text);

  answer.clear();
  for (const auto &[lang, _] : dict)
    answer[lang] = 0;

  for (const auto &token : tokens)
    for (const auto &[lang, translations] : dict)
      for (const auto &translation : translations)
        if (token == translation)
          ++answer[lang];
}

// ----------------------------------------------------------
// Exercicio 4: Palavras Alienígenas
// ----------------------------------------------------------
// TODO
void FunWithHashTables::wordIndex(const vector<string> &words, vector<int> &answer)
{

  unordered_map<string, unsigned> wordMap{};

  if (wordMap.empty())
  {
    unsigned i{0};
    for (int fifth{-4}; fifth < 26; ++fifth)
    {
      for (int fourth{fifth + 1}; fourth < 26; ++fourth)
      {
        for (int third{fourth + 1}; third < 26; ++third)
        {
          for (int second{third + 1}; second < 26; ++second)
          {
            for (int first{second + 1}; first < 26; ++first)
            {
              string s{};

              if (fifth >= 0)
                s += 'a' + fifth;
              if (fourth >= 0)
                s += 'a' + fourth;
              if (third >= 0)
                s += 'a' + third;
              if (second >= 0)
                s += 'a' + second;

              s += 'a' + first;

              wordMap.insert({s, ++i});
            }
          }
          if (third < -1)
            third = -1;
        }
        if (fourth < -1)
          fourth = -1;
      }
      if (fifth < -1)
        fifth = -1;
    }
  }

  for (const auto &word : words)
    answer.push_back(wordMap[word]);
}
