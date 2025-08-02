#include <string>
#include <unordered_map>
#include "movie.h"
#include <fstream>
#include <sstream>
#include <iostream>
#include "parsing.h"
#include <unordered_set>
#include <algorithm>

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
    string movies = "test/movietest.csv";
    string ratings = "test/ratingtest.csv";
    parseMovies(movies, movieMap, movieNames);
    parseRatings(ratings, movieMap);
}

vector<pair<Movie*, int>> approach1(string fmovie, string smovie, unordered_map<int,Movie>& movieMap, unordered_map<string, Movie*>& movieNames) {
    vector<pair<Movie*, int>> result;

    if (movieNames.find(fmovie) == movieNames.end()) {
        cerr << " Movie: " << fmovie << " not found \n";
        return {};
    }
    Movie& movie1 = *movieNames.at(fmovie);
    Movie& movie2 = *movieNames.at(smovie);

    vector<string> genres1 = movie1.getGenres();
    int id1 = movie1.getId();
    vector<string> genres2 = movie2.getGenres();
    int id2 = movie2.getId();

    //find common genres
    vector<string> common;

    for (auto genre : genres1) {
        if (count(genres2.begin(),genres2.end(),genre) != 0) {
            common.push_back(genre);
        }
    }



    //looking at the common genres - delete 
    for (auto ele : common) {
        cout << ele << " | \n";
    }



    for (auto& pair : movieMap) {
        int id = pair.first;
        Movie& movie = pair.second;

        //makes sure the base movies aren't being looked at
        if (id == id1 || id == id2) {
            continue;
        }

        vector<string> genres = movie.getGenres();
        int count = 0;
        //count how many genres are in the similar section
        for (auto gen : genres) {
            if (std::count(common.begin(),common.end(), gen) != 0) {
                count++;
            }
        }
        if (count > 0) {
            result.emplace_back(&movie, count);
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

vector<pair<Movie*, int>> queueApproach(string fmovie, string smovie, unordered_map<int, Movie>& movieMap, unordered_map<string, Movie*>& movieNames) {
    vector<pair<Movie*, int>> result;

    if (movieNames.find(fmovie) == movieNames.end()) {
        cerr << " Movie: " << fmovie << " not found\n";
        return {};
    }
    Movie& movie1 = *movieNames.at(fmovie);
    if (movieNames.find(smovie) == movieNames.end()) {
        cerr << " Movie: " << smovie << " not found\n";
        return {};
    }
    Movie& movie2 = *movieNames.at(smovie);

    vector<string> genres1 = movie1.getGenres();
    vector<string> genres2 = movie2.getGenres();
    int id1 = movie1.getId();
    int id2 = movie2.getId();

    vector<string> commonGenres;

    for (const auto& gen : genres1) {
        if ( count(genres2.begin(),genres2.end(), gen) ) {
            commonGenres.push_back(gen);
        }
    }

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

    while (!pq.empty()) {
        auto topPair = pq.top();
        pq.pop();
        int count = topPair.first;
        Movie* movie = topPair.second;
        result.emplace_back(movie, count);
    }
    return result;
}
