#include "MovieRentingSystem.hpp"

struct Entry {
    int shop, price;
    bool rented;
};
struct CompareMovie {
    bool operator()(const Entry &a, const Entry &b) const {
        if (a.price == b.price) return a.shop < b.shop;
        return a.price < b.price;
    }
};

struct RentedEntry {
    int shop, movie, price;
};
struct CompareRented {
    bool operator()(const RentedEntry &a, const RentedEntry &b) const {
        if (a.price == b.price) {
            if (a.shop == b.shop) return a.movie < b.movie;
            return a.shop < b.shop;
        }
        return a.price < b.price;
    }
};

class Impl {
public:
    int n;
    unordered_map<long long, int> priceLookup;
    map<int, multiset<Entry, CompareMovie>> movieInfo;
    multiset<RentedEntry, CompareRented> rented;
    unordered_map<long long, multiset<Entry, CompareMovie>::iterator> movieIter;
    unordered_map<long long, multiset<RentedEntry, CompareRented>::iterator> rentedIter;

    long long encode(int shop, int movie) { return ((long long)shop << 32) | movie; }
};

static unique_ptr<Impl> impl;

MovieRentingSystem::MovieRentingSystem(int n, vector<vector<int>>& entries) {
    impl = make_unique<Impl>();
    impl->n = n;
    for (auto &e : entries) {
        int shop = e[0], movie = e[1], price = e[2];
        long long key = impl->encode(shop, movie);
        impl->priceLookup[key] = price;
        auto it = impl->movieInfo[movie].insert({shop, price, false});
        impl->movieIter[key] = it;
    }
}

vector<int> MovieRentingSystem::search(int movie) {
    vector<int> res;
    if (!impl->movieInfo.count(movie)) return res;
    for (auto &entry : impl->movieInfo[movie]) {
        if (!entry.rented) {
            res.push_back(entry.shop);
            if (res.size() == 5) break;
        }
    }
    return res;
}

void MovieRentingSystem::rent(int shop, int movie) {
    long long key = impl->encode(shop, movie);
    auto &ms = impl->movieInfo[movie];
    auto it = impl->movieIter[key];

    Entry updated = *it;
    ms.erase(it);
    updated.rented = true;
    impl->movieIter[key] = ms.insert(updated);

    impl->rentedIter[key] = impl->rented.insert({shop, movie, impl->priceLookup[key]});
}

void MovieRentingSystem::drop(int shop, int movie) {
    long long key = impl->encode(shop, movie);
    auto &ms = impl->movieInfo[movie];
    auto it = impl->movieIter[key];

    Entry updated = *it;
    ms.erase(it);
    updated.rented = false;
    impl->movieIter[key] = ms.insert(updated);

    impl->rented.erase(impl->rentedIter[key]);
    impl->rentedIter.erase(key);
}

vector<vector<int>> MovieRentingSystem::report() {
    vector<vector<int>> res;
    int count = 0;
    for (auto &re : impl->rented) {
        res.push_back({re.shop, re.movie});
        if (++count == 5) break;
    }
    return res;
}
