#include "prepareInput.h"
#include <vector>
#include <string>
#include <iostream>
#include "movie.h"
#include <unordered_set>

using namespace std;

//not part of approach, apart of setup
PreparedInput PreparedInput::prepare(const std::string& fmovie, const std::string& smovie, const std::unordered_map<std::string, Movie*>& movieNames) {
    PreparedInput inputs;

    //finds the names in the map and checks to see if they exist
    const auto it1 = movieNames.find(fmovie);
    const auto it2 = movieNames.find(smovie);

    if (it1 == movieNames.end()) {
        cout << "Error: First movie not found!" << endl;
        return inputs;
    }
    if (it2 == movieNames.end()) {
        cout << "Error: Second movie not found!" << endl;
        return inputs;
    }

    Movie* movie1 = it1->second;
    Movie* movie2 = it2->second;
  
    std::vector<string> genres1 = movie1->getGenres(); 
    std::vector<string> genres2 = movie2->getGenres();

    std::unordered_set<std::string> genres(genres1.begin(), genres1.end());
    std::vector<std::string> common;

    for (const auto genre : movie2->getGenres()) {
        if (genres.count(genre)) {
            common.push_back(genre);
        }
    }
    inputs.common = common;

    inputs.empty = inputs.common.empty();
    inputs.id1 = movie1->getId();
    inputs.id2 = movie2->getId();
    return inputs;
}

int PreparedInput::getId1() const {
    return id1;
}

int PreparedInput::getId2() const {
    return id2;
}

const std::vector<std::string>& PreparedInput::getCommon() const {
    return common;
}