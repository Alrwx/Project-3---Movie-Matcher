#pragma once
#include <string>
#include <unordered_map>
#include "movie.h"

//.h file for cleaner code

//parses movie.csv and makes a map with Movie objects, with name, id, and genres
void parseMovies(const std::string& filename, std::unordered_map<int,Movie>& movieMap, std::unordered_map<std::string, Movie*>& movieNames);

//parses the csvratings.csv and puts in the movie ratings into the movieMap
void parseRatings(const std::string& filename, std::unordered_map<int, Movie>& movieMap);

//combines the two parsing functions
void parseData(std::unordered_map<int,Movie>& movieMap, std::unordered_map<std::string, Movie*>& movieNames);

//approach 1: using a map
void approach1(std::string fmovie, std::string smovie, std::unordered_map<int,Movie>& movieMap, std::unordered_map<std::string, Movie*>& movieNames);
//approach 2:
