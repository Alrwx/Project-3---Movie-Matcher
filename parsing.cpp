#include <string>
#include <unordered_map>
#include "movie.h"
#include <fstream>
#include <sstream>
#include <iostream>
#include "parsing.h"
#include <set>

void parseMovies(const std::string& filename, std::unordered_map<int,Movie>& movieMap, std::unordered_map<std::string, Movie*>& movieNames) {
    std::ifstream file(filename);
    std::string line;
    //gets the first line, its just the header
    std::getline(file, line);
    while (std::getline(file, line)) {
        std::stringstream ss(line);
        std::string idStr;
        std::string nameStr;
        std::string genreStr;

        std::getline(ss, idStr, ',');
        int movID = std::stoi(idStr);
        std::getline(ss, nameStr, ',');

        Movie movie(nameStr, movID);

        std::getline(ss, genreStr, ',');
        //parsing through the different genres
        std::stringstream gss(genreStr);
        std::string genre;
        while(std::getline(gss, genre, '|')) {
            movie.addGenre(genre);
        }
        
        //add to map
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
        std::string userStr;
        std::string movStr;
        std::string ratStr;

        //gets the different values and converts them to their respective datatype
        std::getline(ss, userStr, ',');
        int userId = std::stoi(userStr);
        std::getline(ss, movStr, ',');
        int movieID = std::stoi(movStr);
        std::getline(ss, ratStr, ',');
        double rating = std::stod(ratStr);

        //adds the rating to the map
        movieMap.at(movieID).addRating(rating);
    }
}

//combines the two parsing functions
void parseData(std::unordered_map<int,Movie>& movieMap, std::unordered_map<std::string, Movie*>& movieNames) {
    std::string movies = "test/movietest.csv";
    std::string ratings = "test/ratingtest.csv";
    parseMovies(movies, movieMap, movieNames);
    parseRatings(ratings, movieMap);
}

void approach1(std::string fmovie, std::string smovie, std::unordered_map<int,Movie>& movieMap, std::unordered_map<std::string, Movie*>& movieNames) {
    Movie movie1 = *movieNames.at(fmovie);
    Movie movie2 = *movieNames.at(smovie);

    std::vector<std::string> genres1 = movie1.getGenres();
    std::vector<std::string> genres2 = movie2.getGenres();

    //find common genres
    std::set<std::string> genres;


    return;
}