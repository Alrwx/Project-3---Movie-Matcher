#pragma once
#include <string>
#include <vector>
#include <unordered_map>
#include "Movie.h"

struct PreparedInput {
    private:
        int id1;
        int id2;
        bool empty = true;
        std::vector<std::string> common;

    public:
        // Prepares the input by finding the movie IDs and common genres, not apart of the approach!
        PreparedInput prepare(const std::string& fmovie, const std::string& smovie, const std::unordered_map<std::string, Movie*>& movieNames);
        int getId1() const;
        int getId2() const;
        const std::vector<std::string>& getCommon() const;
};