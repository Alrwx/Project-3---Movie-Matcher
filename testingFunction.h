#pragma once
#include <unordered_map>
#include <string>
#include <vector>
#include "movie.h"
#include "Storage.h"

void printMovieNames(std::unordered_map<std::string, Movie*>& movieNames);
void printG(std::vector<Movie*>& g, int c);
void printMov(std::vector<Storage>& store);
void printResults(const std::vector<Storage>& result);
