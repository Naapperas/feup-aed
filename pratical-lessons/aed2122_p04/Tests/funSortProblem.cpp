#include "funSortProblem.h"
#include <algorithm>

FunSortProblem::FunSortProblem() {}


//-----------------------------------------------------------------

// TODO
void FunSortProblem::expressLane(vector<Product> &products, unsigned k) {

    std::sort(products.begin(), products.end(), [&](const Product& a, const Product& b){
        if (a.getPrice() == b.getPrice())
            return a.getWeight() <= b.getWeight();

        return a.getPrice() < b.getPrice();
    });

    vector<Product> tmp;
    auto currElem = products.begin();
    std::copy_if(products.begin(), products.end(), std::back_inserter(tmp), [&](const Product& p) { return std::distance(products.begin(), currElem++) < k; } );
    products = tmp;

    // O(n*log(n) + n)
}

// TODO
int FunSortProblem::minDifference(const vector<unsigned> &values, unsigned nc) {

    if (nc > values.size()) return -1;

    vector<unsigned> tmp = values;

    std::sort(tmp.begin(), tmp.end());

    unsigned minDiff = INT32_MAX;

    for (int i = 0; i < values.size() - nc + 1; ++i) {

        unsigned diff = tmp[i+nc - 1] - tmp[i];

        if (diff < minDiff) minDiff = diff;
    }

    return minDiff;
}


// TODO
unsigned FunSortProblem::minPlatforms (const vector<float> &arrival, const vector<float> &departure) {

    if (arrival.size() != departure.size()) return -1;

    vector<float> arr = arrival, dep = departure;

    std::sort(arr.begin(), arr.end());
    std::sort(dep.begin(), dep.end());

    unsigned numTrains = 1, maxTrains = 0;

    size_t c = 1, p = 0;

    while (c < arr.size()) {

        if (arr[c] <= dep[p]) {
            c++;
            numTrains++;
        } else {
            p++;
            numTrains--;
        }

        if (numTrains > maxTrains) maxTrains = numTrains;
    }

    return maxTrains;
}


// TODO

void FunSortProblem::nutsBolts(vector<Piece> &nuts, vector<Piece> &bolts) {

    vector<Piece> newBolts,  newNuts;

    for (unsigned b = 0; b < bolts.size(); ++b) {

        auto bolt = bolts[b];

        for (unsigned n = 0; n < nuts.size(); ++n) {
            auto nut = nuts[n];

            if (nut.getDiameter() == bolt.getDiameter()) {
                // found the nut-bolt pair
                newBolts.push_back(bolt);
                newNuts.push_back(nut);
                break;
            }
        }
    }

    nuts = newNuts, bolts = newBolts;
}

