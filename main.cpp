#include "movie.h"
#include "parsing.h"
#include "testingFunction.h"
#include <iostream>
#include <unordered_map>
#include <string>
#include "prepareInput.h"
#include "Storage.h"

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

    // printMovieNames(movieNames);

    //testing purposes

    std::string mov1 = "Nixon (1995)";
    std::string mov2 = "Casino (1995)";

    PreparedInput prep;
    prep = prep.prepare(mov1, mov2, movieNames);

    // std::cout << "Common genres found: ";
    // for (const auto& genre : prep.getCommon()) std::cout << genre << " ";
    // std::cout << std::endl;

    // std::cout << mov1 << " : " << mov2 << std::endl;

    std::vector<Storage> result = approach1(prep, movieMap);


    printResults(result);

    // std::vector<std::vector<Movie*>> g;

    
    
}
