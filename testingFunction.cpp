#include "testingFunction.h"
#include <iostream>
#include <unordered_map>
#include <string>
#include <vector>
#include "movie.h"
#include <queue>
#include <unordered_set>
#include "Storage.h"


//prints out the movie names
void printMovieNames(std::unordered_map<std::string, Movie*>& movieNames) {
    int count = 0;
    for (const auto& pair : movieNames) {
            if (count == 5) {
                break;
            }
            count++;
            const Movie* movie = pair.second;
            std::cout << "ID: " << movie->getId() << ", Title: " << pair.first << ", Average Rating: " << movie->getRating() << std::endl;
    }  
}

//prints out approach 1 movies, not in order yet
void printG(const std::vector<Movie*>& g, int c) {
    if (c == 0) {
        return;
    }
    if (g.empty()) {
        std::cout << "No movies with " << c << " genres in common." << std::endl;
        return;
    }
    std::cout << "Movies with " << c << " genres in common" << std::endl;
    for (const auto movie : g) {
        std::cout << "Name: " << movie->getName()
            << " | Rating: " << movie->getRating()
            << " | Genres: ";
        const auto& genres = movie->getGenres();
        for (size_t i = 0; i < genres.size(); ++i) {
            std::cout << genres[i];
            if (i != genres.size() - 1)
                std::cout << ", ";
        }
        std::cout << "\n";
    }
}

// Waleed: Implementing approach2 for a priority heap-based movie recommendation algorithm
std::vector<Movie*> approach2(
    const std::string& fmovie,
    const std::string& smovie,
    std::unordered_map<int, Movie>& movieMap,
    std::unordered_map<std::string, Movie*>& movieNames,
    int topN){

    struct MovieScore{
        Movie* movie;
        int commonGenreCount;
        double rating;

        bool operator<(const MovieScore& other) const{
            if (commonGenreCount == other.commonGenreCount)
                return rating < other.rating;
            return commonGenreCount < other.commonGenreCount;
        }
    };

    std::priority_queue<MovieScore> heap;

    Movie& movie1 = *movieNames.at(fmovie);
    Movie& movie2 = *movieNames.at(smovie);

    std::unordered_set<std::string> commonGenres;
    for (const auto& g1 : movie1.getGenres()){
        for (const auto& g2 : movie2.getGenres()){
            if (g1 == g2) commonGenres.insert(g1);
        }
    }

    for (auto& [id, movie] : movieMap){
        if (id == movie1.getId() || id == movie2.getId()) continue;

        int genreMatch = 0;
        for (const auto& g : movie.getGenres()){
            if (commonGenres.count(g)) genreMatch++;
        }

        if (genreMatch > 0){
            heap.push({&movie, genreMatch, movie.getRating()});
        }
    }

    std::vector<Movie*> result;
    while(!heap.empty() && result.size() < static_cast<size_t>(topN)){
        result.push_back(heap.top().movie);
        heap.pop();
    }

    return result;
}

