# Movie Renting System (C++)

This project implements a simulation of a Movie Renting System that supports:

- Searching for a movie (top 5 cheapest shops)
- Renting a movie
- Dropping a rented movie
- Reporting the cheapest 5 currently rented movies

## Build & Run

```bash
g++ -std=c++17 -Iinclude src/MovieRentingSystem.cpp tests/test.cpp -o movie_renting_system
./movie_renting_system
