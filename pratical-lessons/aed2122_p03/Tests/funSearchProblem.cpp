#include "funSearchProblem.h"

FunSearchProblem::FunSearchProblem() {}

//-----------------------------------------------------------------

// Due to a minor inconvenience, the exercises implemented have been erased

// TODO
int FunSearchProblem::facingSun(const vector<int> & values) {
    return 0;
}

// TODO
int FunSearchProblem::squareR(int num) {
    return 0;
}

// TODO
int FunSearchProblem::smallestMissingValue(const vector<int> & values) {
    return 0;
}

// TODO
int FunSearchProblem::minPages(const vector<int> & values, int numSt) {

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

