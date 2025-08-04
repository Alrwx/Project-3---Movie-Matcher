#include <string>
#include <unordered_map>
#include "movie.h"
#include <fstream>
#include <sstream>
#include <iostream>
#include "parsing.h"
#include <algorithm>
#include "Storage.h"
#include "prepareInput.h"
#include "CustomMap.h"
#include <unordered_set>
#include <algorithm>
#include <queue>
#include <vector>

using namespace std;

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

void parseRatings(const string& filename, unordered_map<int,Movie>& movieMap) {
    ifstream file(filename);
    string line;

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
void parseData(unordered_map<int,Movie>& movieMap, unordered_map<string, Movie*>& movieNames) {
    string movies = "files/movies.csv";
    string ratings = "files/csvratings.csv";
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
/*
struct CompareCount {
    bool operator()(const pair<int, Movie*>& m1, const pair<int, Movie*>& m2) {
        if (m1.first != m2.first) {
            return m1.first < m2.first;
        }
        return m1.second->getRating() < m2.second->getRating();
    }

*/
//We have to re-implement this, we have to make a priority queue.
// Queue Approach (preparedInput finds the strings and the ID's)
vector<Storage> queueApproach(const PreparedInput input, unordered_map<int, Movie>& movieMap) {
    int id1 = input.getId1();
    int id2 = input.getId2();
    const vector<string>& commonGenres = input.getCommon();

    const int MAX_COUNT = 5;
    vector<Storage> result(6);
    MoviePQ pq;
    //priority_queue<pair<int, Movie*>,vector<pair<int, Movie*>>, CompareCount> pq;

    for (auto& pair : movieMap) {
        int id = pair.first;
        Movie& movie = pair.second;

        if (id == id1 || id == id2 || movie.getRating() == 0) {continue;}

        vector<string> genres = movie.getGenres();

        int matchCount = 0;

        for (const auto& gen : genres) {
            if (count(commonGenres.begin(),commonGenres.end(), gen)) {
                matchCount++;
            }
        }
        if (matchCount > 0 ) {
            //int ratingInt = static_cast<int>(movie.getRating() * 100);
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

        //Movie* movie = topPair.second;
        /*
        if (count > 0) {
            result[count].addMovie(movie);
        }
    }
    */
    }
    for (int i = 1; i <= MAX_COUNT; i++) {
        result[i].pqSortMovies();
    }
    return result;
}