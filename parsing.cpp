#include <string>
#include <unordered_map>
#include "movie.h"
#include <fstream>
#include <sstream>
#include <iostream>
#include "parsing.h"
#include "Storage.h"
#include "prepareInput.h"
#include "CustomMap.h"
#include <vector>



//combines the two parsing functions
void parseData(std::unordered_map<int,Movie>& movieMap, std::unordered_map<std::string, Movie*>& movieNames) {
    std::string movies = "files/movies.csv";
    std::string ratings = "files/csvratings.csv";
    parseMovies(movies, movieMap, movieNames);
    parseRatings(ratings, movieMap);
}
void parseMovies(const std::string& filename, std::unordered_map<int,Movie>& movieMap, std::unordered_map<std::string, Movie*>& movieNames) {
    std::ifstream file(filename);
    std::string line;
    //gets the first line, its just the header
    std::getline(file, line);  

    while (std::getline(file, line)) {
        std::stringstream ss(line);
        std::string idStr, nameStr, genreStr;

        std::getline(ss, idStr, ',');
        int movID = std::stoi(idStr);
        std::getline(ss, nameStr, ',');
        nameStr = nameStr.substr(0, nameStr.find_last_not_of(" \n\r\t") + 1);
        std::getline(ss, genreStr, ',');

        Movie movie(nameStr, movID);

        std::stringstream gss(genreStr);
        std::string genre;
        while (std::getline(gss, genre, '|')) {
            movie.addGenre(genre);
        }

        movieMap.emplace(movID, movie);
        //another map used just for storing the names, super helpful for the approaches for O(1) lookup
        //cannot do  &movie, since it is a local variable in this function
        movieNames.emplace(nameStr, &movieMap.at(movID));
    }
}

void parseRatings(const std::string& filename, std::unordered_map<int,Movie>& movieMap) {
    std::ifstream file(filename);
    std::string line;

    std::getline(file, line);

    while (std::getline(file, line)) {
        std::stringstream ss(line);
        std::string userStr, movStr, ratStr;

        std::getline(ss, userStr, ',');
        std::getline(ss, movStr, ',');
        std::getline(ss, ratStr, ',');

        int movieID;
        double rating;

        try {
            movieID = std::stoi(movStr);
            rating = std::stod(ratStr);
        } catch (...) {
            std::cerr << "Skipping invalid line: " << line << '\n';
            continue;
        }

        auto it = movieMap.find(movieID);
        if (it != movieMap.end()) {
            it->second.addRating(rating);
        } else {
            std::cerr << "Warning: movie ID " << movieID << " not found in movieMap.\n";
        }
    }
}

void printResults(const std::vector<Storage>& result) {
    bool hasMovies = false;
    for (size_t i = 1; i < result.size(); ++i) {
        const std::vector<Movie*>& movies = result[i].getMovies();
        if (!movies.empty()) {
            hasMovies = true;
            std::cout << "Movies with " << i << " common genres:\n";
            int count = 0;
            for (const auto& movie : movies) {
                if (count == 10) {
                    break;
                }
                std::cout << "- ID: " << movie->getId() << ", Title: " << movie->getName() << ", Rating: " << movie->getRating() << "\n";
                count++;
            }
            std::cout << std::endl;
        }
    }
    if (!hasMovies) {
        std::cout << "No movies in common." << std::endl;
    }
}

// Alvin
std::vector<Storage> approach1(const PreparedInput& input, std::unordered_map<int,Movie>& movieMap) {
    //initialie vector with 6 empty storage slots to allow for indexing with []
    std::vector<Storage> result(6);
    CustomHashMap map(6, 0.75f);

    int id1 = input.getId1();
    int id2 = input.getId2();

    for (auto& pair : movieMap) {
        int id = pair.first;
        Movie& movie = pair.second;

        //makes sure the base movies aren't being looked at
        if (id == id1 || id == id2 || movie.getRating() == 0) {
            continue;
        }

        std::vector<std::string> genres = movie.getGenres();
        const std::vector<std::string>& common = input.getCommon();

        int count = 0;
        //count how many genres are in the similar section
        for (auto genre : genres) {
            for (auto selected : common) {
                if (genre == selected) {
                    count++;
                    break; // stops double counting
                }
            }
        }
    
        if (count > 0) {
            std::string key = std::to_string(count);
            if (!map.has(key)) {
                map.insert(key, &result[count]);
            }
            Storage* store = map.get(key);
            store->setCount(count);
            store->addMovie(&movie);
        }
    }

   for (int i = 1; i <= 5; i++) {
        std::string key = std::to_string(i);
        if (map.has(key)) {
            Storage* store = map.get(key);
            store->sortMovies();
            result[i] = *store;
        }
    }
    return result;
}


// Queue Approach (preparedInput finds the strings and the ID's)
std::vector<Storage> queueApproach(const PreparedInput input, std::unordered_map<int, Movie>& movieMap) {
    int id1 = input.getId1();
    int id2 = input.getId2();
    const std::vector<std::string>& commonGenres = input.getCommon();

    const int MAX_COUNT = 5;
    std::vector<Storage> result(6);
    MoviePQ pq;

    for (auto& pair : movieMap) {
        int id = pair.first;
        Movie& movie = pair.second;

        if (id == id1 || id == id2 || movie.getRating() == 0) {continue;}

        std::vector<std::string> genres = movie.getGenres();

        int matchCount = 0;

        for (auto genre : genres) {
            for (auto selected : commonGenres) {
                if (genre == selected) {
                    matchCount++;
                    break; // stops double counting
                }
            }
        }

        if (matchCount > 0 ) {
            pq.push({&movie, matchCount} );
        }
    }

    while (!pq.empty()) {

        auto topPair = pq.top();
        pq.pop();

        Movie* movie = topPair.first;
        int count = topPair.second;


        if (count <= MAX_COUNT) {
            result[count].addMovie(movie);
            result[count].setCount(count);
        }
    }
    for (int i = 1; i <= MAX_COUNT; i++) {
        result[i].pqSortMovies();
    }
    return result;
}