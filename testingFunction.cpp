#include "testingFunction.h"
#include <iostream>
#include <unordered_map>
#include <string>
#include <vector>
#include "movie.h"

//test file used to see if the parsing works correctly

//prints out the movie names
void printMovieNames(std::unordered_map<std::string, Movie*>& movieNames) {
    for (const auto& pair : movieNames) {
            const Movie* movie = pair.second;
            std::cout << "ID: " << movie->getId() << ", Title: " << pair.first << ", Average Rating: " << movie->getRating() << std::endl;
    }
}

//prints out approach 1 movies, not in order yet
void printG(std::vector<Movie*>& g, int c) {
    if (c == 0) {
        return;
    }
    if (g.empty()) {
        std::cout << "No movies with " << c << " genres in common." << std::endl;
        return;
    }
    std::cout << "Movies with " << c << " genres in common" << std::endl;
    for (const auto mov : g) {
        Movie* movie = mov;
        std::cout << "Name: " << movie->getName() << " | Rating: " << movie->getRating() << " | Genres: ";
        for (auto gen : movie->getGenres()) {
            std::cout << gen << " ,";
        }
        std::cout << std::endl;
    }
}