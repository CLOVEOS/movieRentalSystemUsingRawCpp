#include "MovieRentingSystem.hpp"
#include <iostream>

int main() {
    vector<vector<int>> entries = {
        {0, 1, 5}, {0, 2, 6}, {0, 3, 7},
        {1, 1, 4}, {1, 2, 7}, {2, 1, 5}
    };

    MovieRentingSystem mrs(3, entries);

    auto s1 = mrs.search(1); // should return [1, 0, 2]
    cout << "Search for movie 1: ";
    for (auto x : s1) cout << x << " ";
    cout << endl;

    mrs.rent(1, 1);
    auto s2 = mrs.search(1); // [0, 2]
    cout << "Search after renting shop 1 movie 1: ";
    for (auto x : s2) cout << x << " ";
    cout << endl;

    auto report = mrs.report();
    cout << "Report: ";
    for (auto &x : report) cout << "(" << x[0] << "," << x[1] << ") ";
    cout << endl;

    mrs.drop(1, 1);
    auto s3 = mrs.search(1); // back to [1, 0, 2]
    cout << "Search after drop: ";
    for (auto x : s3) cout << x << " ";
    cout << endl;

    return 0;
}
