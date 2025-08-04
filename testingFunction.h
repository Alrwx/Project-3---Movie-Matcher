#pragma once
#include <unordered_map>
#include <string>
#include <vector>
#include "movie.h"
#include "Storage.h"

void printMovieNames(std::unordered_map<std::string, Movie*>& movieNames);
void printG(const std::vector<Movie*>& g, int c);

void printMov(std::vector<Storage>& store);
std::vector<Movie*> approach2(const std::string& fmovie,
    const std::string& smovie,
    std::unordered_map<int, Movie>& movieMap,
    std::unordered_map<std::string, Movie*>& movieNames,
    int topN = 10);