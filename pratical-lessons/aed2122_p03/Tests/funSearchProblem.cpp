#include "funSearchProblem.h"

FunSearchProblem::FunSearchProblem() {}

//-----------------------------------------------------------------

// TODO
int FunSearchProblem::facingSun(const vector<int> & values) {

    if (values.empty()) return 0;

    int facingSun = 1;

    int currentHeight = values[0];

    for (int i : values)
        if (i > currentHeight) {
            facingSun++;
            currentHeight = i;
        }

    return facingSun;
}

// TODO
int FunSearchProblem::squareR(int num) {

    int max = num;
    int min = 0;
    int mid = (max + min)/2;

    while (max > min) {

        if (max - min == 1) return min;

        int candidate = mid*mid;

        if (candidate == num)
            return mid;
        else if (candidate > num)
            max = mid;
        else if (candidate < num)
            min = mid;

        mid = (max + min)/2;
    }
    return mid;
}

// TODO
int FunSearchProblem::smallestMissingValue(const vector<int> & values) {

    bool negs = true;
    for (auto value : values)
        if (value > 0) {
            negs = false;
            break;
        }
    if (negs) return 0;

    vector<bool> tmp(values.size());
    for (auto value : values)
        if (value > 0 && value <= tmp.size())
            tmp.at(value-1) = true;

    for (int i = 0; i < tmp.size(); i++)
        if (!tmp[i]) return i + 1;

    return tmp.size() + 1;
}

// TODO
int FunSearchProblem::minPages(const vector<int> & values, int numSt) {

    if (values.size() < numSt)
        return -1;

    int max = INT32_MIN, sum = 0;

    for (int value : values) {
        sum += value;
        if (value > max) max = value;
    }

    int low = max, high = sum;

    // bin search

    while (low < high) {

        int middle = (high + low) / 2;

        int painters = 1;
        int s = 0;

        for (int value : values) {
            s += value;
            if (s > middle) {
                s = value;
                painters++;
            }
        }

        if (painters <= numSt) high = middle;
        else low = middle + 1;
    }

    return low;
}

