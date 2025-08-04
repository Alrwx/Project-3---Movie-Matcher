#include "Storage.h"
#include <algorithm>

Storage::Storage() : count(0) {}

Storage::Storage(int c) : count(c) {}

void Storage::addMovie(Movie* mov) {
    for (auto* m : movies) {
        if (m == mov) return;
    }
    movies.push_back(mov);
}

void Storage::setCount(int n) {
    count = n;
}

int Storage::getCount() const {
    return count;
}

const std::vector<Movie*>& Storage::getMovies() const {
    return movies;
}

void Storage::sortMovies() {
    //insertion sort! O(n^2)
  for (int i = 1; i < movies.size(); i++) {
        Movie* key = movies[i];
        int keyRating = key->getRating();
        int j = i - 1;
        while (j >= 0 && movies[j]->getRating() < keyRating) {
            movies[j + 1] = movies[j];
            j--;
        }
        movies[j + 1] = key;
    }
}