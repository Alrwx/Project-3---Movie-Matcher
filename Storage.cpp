#include "Storage.h"
#include <algorithm>
#include <vector>
#include <ios>

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

void Storage::mergeMovies(std::vector<Movie*>& movies, int left, int mid, int right) {
    int m1 = mid - left + 1;
    int m2 = right - mid;

    std::vector<Movie*> L(m1), R(m2);

    for (int i = 0; i < m1; ++i) {
        L[i] = movies[left+i];
    }
    for (int i = 0; i < m2; ++i) {
        R[i] = movies[mid+1+i];
    }

    int i = 0, j = 0, k = left;
    while (i < m1 && j < m2) {
        if (L[i]->getRating() >= R[j]->getRating()) {
            movies[k++] = L[i++];
        }else {
            movies[k++] = R[j++];
        }
    }
    while (i < m1) {
        movies[k++] = L[i++];
    }
    while (j < m2) {
        movies[k++] = R[j++];
    }
}

void Storage::mergeSortMovies(std::vector<Movie*>& movies, int left, int right) {
    if (left < right) {
        int mid = left + (right - left) / 2;
        mergeSortMovies(movies, left, mid);
        mergeSortMovies(movies, mid + 1, right);
        mergeMovies(movies, left, mid, right);
    }
}

void Storage::pqSortMovies() {
    if (movies.size() <= 1) {return;};
    mergeSortMovies(movies, 0, movies.size() - 1);
}
