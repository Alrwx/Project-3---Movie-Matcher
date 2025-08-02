#pragma once
#include <unordered_map>
#include <string>
#include <vector>
#include "movie.h"

void printMovieNames(std::unordered_map<std::string, Movie*>& movieNames);
void printG(std::vector<Movie*>& g, int c);
