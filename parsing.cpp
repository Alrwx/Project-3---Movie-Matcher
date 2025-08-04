#include <string>
#include <unordered_map>
#include "movie.h"
#include <fstream>
#include <sstream>
#include <iostream>
#include "parsing.h"
#include "CustomMap.h"
#include <unordered_set>
#include <algorithm>
#include <queue>
#include <vector>


struct CompareCount {
    bool operator()(const std::pair<int, Movie*>& m1, const std::pair<int, Movie*>& m2) {
        if (m1.first != m2.first) {
            return m1.first < m2.first;
        }
        return m1.second->getRating() < m2.second->getRating();
    }
};

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

        auto [it, inserted] = movieMap.emplace(movID, movie);
        if (!inserted) {
            std::cerr << "Duplicate movie ID found: " << movID << std::endl;
        }
        //add to map
        movieNames.emplace(nameStr, &it->second);
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




//combines the two parsing functions
void parseData(std::unordered_map<int,Movie>& movieMap, std::unordered_map<std::string, Movie*>& movieNames) {
    std::string movies = "files/movies.csv";
    std::string ratings = "files/csvratings.csv";
    parseMovies(movies, movieMap, movieNames);
    parseRatings(ratings, movieMap);
}

// Alvin
std::vector<Storage> approach1(const PreparedInput& input, std::unordered_map<int,Movie>& movieMap) {
    //initialie vector with 6 empty storage slots to allow for indexing with []
    std::vector<Storage> result(6);
    CustomHashMap map(6, 0.75f);

    int id1 = input.getId1();
    int id2 = input.getId2();

    std::priority_queue<std::pair<int, Movie*>, std::vector<std::pair<int, Movie*>>, CompareCount> pq;
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




// Kevin
std::vector<std::pair<Movie*, int>> queueApproach(std::string fmovie, std::string smovie, std::unordered_map<int, Movie>& movieMap, std::unordered_map<std::string, Movie*>& movieNames) {
    std::vector<std::pair<Movie*, int>> result;

    if (movieNames.find(fmovie) == movieNames.end()) {
        std::cerr << " Movie: " << fmovie << " not found\n";
        return {};
    }
    if (movieNames.find(smovie) == movieNames.end()) {
        std::cerr << " Movie: " << smovie << " not found\n";
        return {};
    }

    Movie& movie1 = *movieNames.at(fmovie);
    Movie& movie2 = *movieNames.at(smovie);

    std::vector<std::string> genres1 = movie1.getGenres();
    std::vector<std::string> genres2 = movie2.getGenres();
    int id1 = movie1.getId();
    int id2 = movie2.getId();

    std::vector<std::string> commonGenres;
    for (const auto& gen : genres1) {
        if (std::count(genres2.begin(), genres2.end(), gen)) {
            commonGenres.push_back(gen);
        }
    }

    std::priority_queue<std::pair<int, Movie*>, std::vector<std::pair<int, Movie*>>, CompareCount> pq;

    for (auto& pair : movieMap) {
        int id = pair.first;
        Movie& movie = pair.second;

        if (id == id1 || id == id2) continue;

        std::vector<std::string> genres = movie.getGenres();
        int matchCount = 0;
        for (const auto& gen : genres) {
            if (std::count(commonGenres.begin(), commonGenres.end(), gen)) {
                matchCount++;
            }
        }

        if (matchCount > 0) {
            pq.emplace(matchCount, &movie);
        }
    }

    while (!pq.empty()) {
        auto topPair = pq.top();
        pq.pop();
        result.emplace_back(topPair.second, topPair.first); // Movie*, count
    }

    return result;
}