#include "movie.h"
#include "parsing.h"
#include <iostream>
#include <unordered_map>
#include <string>


void printG(std::vector<Movie*>& g, int c) {
    std::cout << "" << std::endl;
    if (g.empty()) {
        std::cout << "No movies with " << c << " genres in common." << std::endl;
        return;
    }
    std::cout << "Movies with " << c << " genres in common" << std::endl;
    for (const auto mov : g) {
        Movie* movie = mov;
        std::cout << "Name: " << movie->getName() << " | Rating: " << movie->getRating() << " | Genres: " << std::endl;
        for (auto gen : movie->getGenres()) {
            std::cout << "\t" << gen << " ,";
        }
    }
}

int main() {
//     std::cout << "1. Enter First Movie Title" << std::endl;
//     std::cout << "2. Enter Second Movie Title" << std::endl;
//     std::cout << "3. Compute Data" << std::endl;
//     std::cout << "4. Display Top Matches" << std::endl;
//     std::cout << "5. Exit" << std::endl;

    //testing purposes
    std::unordered_map<int, Movie> movieMap;
    std::unordered_map<std::string, Movie*> movieNames;
    // std::string movieCSV = "test/movietest.csv";
    // std::string ratingCSV = "test/ratingtest.csv";

    parseData(movieMap, movieNames);

    // for (const auto& pair : movieNames) {
    //     const Movie* movie = pair.second;
    //     std::cout << "ID: " << movie->getId() << ", Title: " << pair.first << ", Average Rating: " << movie->getRating() << std::endl;
    // } -- this works fine!
    std::string mov1 = "The Matrix";
    std::string mov2 = "Inception";

    std::vector<std::pair<Movie*, int>> result = approach1(mov1, mov2, movieMap, movieNames);

    // for (auto ele : result) {
    //     std::cout << ele << " | " << std::endl;
    // } -- this works fine!
    std::vector<Movie*> g1, g2, g3;

    for (const auto& pair : result) {
        if (pair.second == 1) {
            g1.push_back(pair.first);
        }
        else if (pair.second == 2) {
            g2.push_back(pair.first);
        }
        else {
            g3.push_back(pair.first);
        }
    }

    printG(g1, 1);
    printG(g2, 2);
    printG(g3, 3);
    
}
