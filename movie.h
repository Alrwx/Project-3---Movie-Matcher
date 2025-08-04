#pragma once
#include <string>
#include <vector>
#include <utility>


class Movie {
    private:
        std::string name;
        int id;
        std::vector<std::string> genres;
        double rating_sum = 0.0;
        int rating_count = 0;

    public:
        Movie(std::string n, int i);
        void addGenre(std::string genre);
        void addRating(double rate);

        double getRating() const;
        int getId() const;
        const std::vector<std::string>& getGenres() const;
        std::string getName() const;
};

using namespace std;
class MoviePQ {
    vector<pair<Movie*, int>> data;

    void heapifyUp(int i);
    void heapifyDown(int i);
    bool compare(const pair<Movie*, int>& p1, const pair<Movie*, int>& p2) {
        return p1.first->getRating() < p2.first->getRating();
    }
    public:
    void push(pair<Movie*, int> item);
    void pop();
    pair<Movie*, int> top();
    bool empty() const;
    size_t size() const;

};