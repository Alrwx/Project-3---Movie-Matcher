#include <string>
#include <vector>

class Movie {
    private:
        std::string name;
        int id;
        int rating;
        std::vector<std::string> genres;
    public:
        Movie(std::string n, int i) : name(n), id(i) {}
        void addGenre(std::string genre) {
            genres.push_back(genre);
        }
        void addRating(int rate) {
            rating = rate;
        }
};