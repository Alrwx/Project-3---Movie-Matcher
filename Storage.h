#pragma once
#include "movie.h"
#include <vector>

class Storage{
    private:
        int count;
        std::vector<Movie*> movies;
    public:
        Storage();
        Storage(int c);

        void addMovie(Movie* mov);
        void setCount(int n);
        int getCount() const;
        const std::vector<Movie*>& getMovies() const;

        void sortMovies();
};