#pragma once
#include <string>
#include <vector>

class Movie {
    private:
        std::string name;
        int id;
        double rating = 0.0;
        std::vector<std::string> genres;

        double rating_sum = 0.0;
        int rating_count = 0;

    public:
        Movie(std::string n, int i);
        void addGenre(std::string genre);
        void addRating(double rate);

        double getRating() const;
        int getId() const;
        std::vector<std::string> getGenres() const;
        std::string getName() const;
};