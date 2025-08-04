#pragma once
#include <string>
#include <unordered_map>
#include "movie.h"
#include "parsing.h"
#include <queue>
#include <utility>
#include "prepareInput.h"
#include "Storage.h"

//.h file for cleaner code

//parses movie.csv and makes a map with Movie objects, with name, id, and genres
void parseMovies(const std::string& filename, std::unordered_map<int,Movie>& movieMap, std::unordered_map<std::string, Movie*>& movieNames);

//parses the csvratings.csv and puts in the movie ratings into the movieMap
void parseRatings(const std::string& filename, std::unordered_map<int, Movie>& movieMap);

//combines the two parsing functions, making all the movies being stored within a map.
void parseData(std::unordered_map<int,Movie>& movieMap, std::unordered_map<std::string, Movie*>& movieNames);

//approach 1: Custom DataType
std::vector<Storage> approach1(const PreparedInput& input, std::unordered_map<int,Movie>& movieMap);

//approach 2: Custom Priority Queue
using namespace std;
vector<pair<Movie*, int>> queueApproach(string fmovie, string smovie, unordered_map<int, Movie>& movieMap, unordered_map<string, Movie*>& movieNames);

void printResults(const std::vector<Storage>& result);
