#include <string>
#include <unordered_map>
#include "movie.h"
#include <fstream>
#include <sstream>
#include <iostream>

void parseMovies(const std::string& filename, std::unordered_map<int,Movie>& movieMap) {
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