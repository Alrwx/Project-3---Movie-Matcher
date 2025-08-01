#include "movie.h"
#include "parsing.h"
#include <iostream>
#include <unordered_map>
#include <string>


int main() {
//     std::cout << "1. Enter First Movie Title" << std::endl;
//     std::cout << "2. Enter Second Movie Title" << std::endl;
//     std::cout << "3. Compute Data" << std::endl;
//     std::cout << "4. Display Top 10 Matches" << std::endl;
//     std::cout << "5. Exit" << std::endl;

    //testing purposes
    std::unordered_map<int, Movie> movieMap;
    std::unordered_map<std::string, Movie*> movieNames;
    // std::string movieCSV = "test/movietest.csv";
    // std::string ratingCSV = "test/ratingtest.csv";

    parseData(movieMap, movieNames);

    for (const auto& pair : movieNames) {
        const Movie* movie = pair.second;
        std::cout << "ID: " << movie->getId() << ", Title: " << pair.first << ", Average Rating: " << movie->getRating() << std::endl;
    }
}
