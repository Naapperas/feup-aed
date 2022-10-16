#include <iostream>
#include <vector>

using namespace std;

template <class T>
class MyVector {
    vector<T> values;
public:
    MyVector();
    ~MyVector();
    void push_back(T v1);
    vector<T> getValues() const;
    T max() const;
    bool hasDuplicates() const;
    void removeDuplicates() ;
};


// exception EmptyVector
class EmptyVector
{ };

// methods
template <class T>
MyVector<T>::MyVector() {}

template <class T>
MyVector<T>::~MyVector() {}

template <class T>
void MyVector<T>::push_back(T v1) {
    values.push_back(v1);
}

template <class T>
vector<T> MyVector<T>::getValues() const {
    return values;
}

//---------------------------------

template <class T>
T MyVector<T>::max() const {
    if (this->values.size() == 0) throw EmptyVector();

    T vmax = *this->values.begin();

    for (auto it = (this->values.cbegin() += 1); it != this->values.cend(); it++)
        if (*it > vmax)
            vmax = *it;

	return vmax;
}

template<class T>
bool MyVector<T>::hasDuplicates() const {

    vector<T> vals;

    vals.push_back(this->values.at(0));

    for (auto it = (this->values.cbegin() += 1); it != this->values.cend(); it++) {
        for (const T& val : vals) if (val == *it) return true;
        vals.push_back(*it);
    }

	return false;
}

template<class T>
void MyVector<T>::removeDuplicates() {

    vector<T> vals;

    vals.push_back(this->values.at(0));

    for (auto it = (this->values.begin() += 1); it != this->values.end(); it++) {
        for (const T& val : vals) if (val == *it) goto cnt;
        vals.push_back(*it);
        cnt:; // to serve as a label for continuing the outter-most loop
    }

    this->values = vals;
}

