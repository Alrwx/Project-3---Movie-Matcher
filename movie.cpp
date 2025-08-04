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

