#include "movie.h"
#include "parsing.h"
#include "testingFunction.h"
#include <iostream>
#include <unordered_map>
#include <string>

int main() {
    //basic structure/interface of the terminal:
//     std::cout << "1. Enter First Movie Title" << std::endl;
//     std::cout << "2. Enter Second Movie Title" << std::endl;
//     std::cout << "3. Compute Data" << std::endl;
//     std::cout << "4. Display Top Matches" << std::endl;
//     std::cout << "5. Exit" << std::endl;

    //these maps are used for both approaches, important
    std::unordered_map<int, Movie> movieMap;
    std::unordered_map<std::string, Movie*> movieNames;

    parseData(movieMap, movieNames);

    printMovieNames(movieNames);

    //testing purposes

    std::string mov1 = "The Matrix";
    std::string mov2 = "Inception";
    std::vector<std::pair<Movie*, int>> result = approach1(mov1, mov2, movieMap, movieNames);

    // std::vector<std::vector<Movie*>> g;
    std::vector<Movie*> g1, g2, g3;
    std::unordered_map<int, std::vector<Movie*>> g;

    for (const auto& pair : result) {
        int num = pair.second;

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
