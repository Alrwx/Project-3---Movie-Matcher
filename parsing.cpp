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

using namespace std;

void parseMovies(const string& filename, unordered_map<int,Movie>& movieMap, unordered_map<string, Movie*>& movieNames) {
    ifstream file(filename);
    string line;
    //gets the first line, its just the header
    getline(file, line);
    while (getline(file, line)) {
        stringstream ss(line);
        string idStr;
        string nameStr;
        string genreStr;

        getline(ss, idStr, ',');
        int movID = stoi(idStr);
        getline(ss, nameStr, ',');

        Movie movie(nameStr, movID);

        getline(ss, genreStr, ',');
        //parsing through the different genres
        stringstream gss(genreStr);
        string genre;
        while(getline(gss, genre, '|')) {
            movie.addGenre(genre);
        }
        
        //add to map
        movieMap.emplace(movID, movie);
        //another map used just for storing the names, super helpful for the approaches for O(1) lookup
        //cannot do  &movie, since it is a local variable in this function
        movieNames.emplace(nameStr, &movieMap.at(movID));
    }
}

void parseRatings(const string& filename, unordered_map<int,Movie>& movieMap) {
    ifstream file(filename);
    string line;

    getline(file, line);
    while (getline(file, line)) {
        stringstream ss(line);
        string userStr;
        string movStr;
        string ratStr;

        //gets the different values and converts them to their respective datatype
        getline(ss, userStr, ',');
        int userId = stoi(userStr);
        getline(ss, movStr, ',');
        int movieID = stoi(movStr);
        getline(ss, ratStr, ',');
        double rating = stod(ratStr);

        //adds the rating to the map
        movieMap.at(movieID).addRating(rating);
    }
}

//combines the two parsing functions
void parseData(unordered_map<int,Movie>& movieMap, unordered_map<string, Movie*>& movieNames) {
    string movies = "files/movies.csv";
    string ratings = "files/csvratings.csv";
    parseMovies(movies, movieMap, movieNames);
    parseRatings(ratings, movieMap);
}


vector<Storage> approach1(const PreparedInput& input, std::unordered_map<int,Movie>& movieMap) {
    //initialie vector with 6 empty storage slots to allow for indexing with []
    vector<Storage> result(6);
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

        vector<string> genres = movie.getGenres();
        const vector<string>& common = input.getCommon();

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

struct CompareCount {
    bool operator()(const pair<int, Movie*>& m1, const pair<int, Movie*>& m2) {
        if (m1.first != m2.first) {
            return m1.first < m2.first;
        }
        return m1.second->getRating() < m2.second->getRating();
    }
};


//We have to re-implement this, we have to make a priority queue.
// Queue Approach (preparedInput finds the strings and the ID's)
vector<Storage> queueApproach(const PreparedInput input, unordered_map<int, Movie>& movieMap) {
    int id1 = input.getId1();
    int id2 = input.getId2();
    const vector<string>& commonGenres = input.getCommon();


    priority_queue<pair<int, Movie*>,vector<pair<int, Movie*>>, CompareCount> pq;

    for (auto& pair : movieMap) {
        int id = pair.first;
        Movie& movie = pair.second;

        if (id == id1 || id == id2) {continue;}

        vector<string> genres = movie.getGenres();

        int matchCount = 0;

        for (const auto& gen : genres) {
            if (count(commonGenres.begin(),commonGenres.end(), gen)) {
                matchCount++;
            }
        }
        if (matchCount > 0) {
            pq.emplace(matchCount, &movie);
        }
    }

    vector<Storage> result;

    while (!pq.empty()) {
        auto topPair = pq.top();
        pq.pop();
        int count = topPair.first;
        Movie* movie = topPair.second;
        
        if (count > 0) {
            result[count].addMovie(movie);
        }
    }
    return result;
}

void printResults(const std::vector<Storage>& result) {
    bool hasMovies = false;
    for (size_t i = 1; i < result.size(); ++i) {
        const std::vector<Movie*>& movies = result[i].getMovies();
        if (!movies.empty()) {
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