#include "movie.h"

//movie class functions

Movie::Movie(std::string n, int i) : name(n), id(i) {}

void Movie::addGenre(std::string genre) {
            genres.push_back(genre);
        }
void Movie::addRating(double rate) {
    rating_sum += rate;
    rating_count++;       
}

double Movie::getRating() const {
    if (rating_count == 0) return 0.0;
    return rating_sum / rating_count;
}

int Movie::getId() const {
    return id;
}

std::string Movie::getName() const {
    return name;
}

const std::vector<std::string>& Movie::getGenres() const {
    return genres;
}

bool compare(const std::pair<Movie*, int >& p1, const std::pair< Movie*, int>& p2) {
    return p1.second < p2.second;
}

void MoviePQ::heapifyUp(int i) {
    while (i > 0) {
        int parent = (i - 1) / 2;
        if (compare(data[parent], data[i]) ) {
            swap(data[parent], data[i]);
            i = parent;
        }
        else {break;}
    }
}

void MoviePQ::heapifyDown(int i) {
    int size = data.size();
    while (2 * i + 1 < size) {
        int left = 2 * i + 1;
        int right = 2 * i + 2;
        int largest = i;

        if (left < size && compare(data[largest], data[left])) {
            largest = left;
        }
        if (right < size && compare(data[largest], data[left])) {
            largest = right;
        }
        if (largest != i) {
            swap(data[largest], data[i]);
            i = largest;
        }
        else {break;}

    }
}

void MoviePQ::push(std::pair<Movie*, int> item) {
    data.push_back(item);
    heapifyUp(data.size() - 1);
}
void MoviePQ::pop() {
    if (data.empty()) {return;}
    swap(data[0], data.back());
    data.pop_back();
    heapifyDown(0);
}
std::pair<Movie*, int> MoviePQ::top() {
    if (!data.empty()) {
        return data[0];
    }else {
        return {nullptr, -1};
    }
}
bool MoviePQ::empty() const {
    return data.empty();
}

int MoviePQ::size() const {
    return data.size();
}
