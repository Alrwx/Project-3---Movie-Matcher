#include "movie.h"
#include "parsing.h"
#include "testingFunction.h"
#include <iostream>
#include <unordered_map>
#include <string>
#include "prepareInput.h"
#include "Storage.h"
#include <limits>

int main() {
    std::unordered_map<int, Movie> movieMap;
    std::unordered_map<std::string, Movie*> movieNames;
    parseData(movieMap, movieNames);

    std::string mov1 = "", mov2 = "";
    std::vector<Movie*> topMatches;
    std::vector<Storage> storageResult;
    bool dataComputed = false;
    int algoChoice = 0;

    while (true) {
        std::cout << "\n--- Movie Matcher Menu ---\n";
        std::cout << "1. Enter First Movie Title\n";
        std::cout << "2. Enter Second Movie Title\n";
        std::cout << "3. Compute Data\n";
        std::cout << "4. Display Top Matches\n";
        std::cout << "5. Exit\n";
        std::cout << "Select an option (1-5): ";

        int option;
        if (!(std::cin >> option)) {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << "Invalid input. Please enter a number between 1 and 5.\n";
            continue; 
        }
        std::cin.ignore(); 

        if (option == 1) {
            std::cout << "Enter First Movie Title (e.g. The Matrix (1999)): ";
            std::getline(std::cin, mov1);
        }
        else if (option == 2) {
            std::cout << "Enter Second Movie Title (e.g. Inception (2010)): ";
            std::getline(std::cin, mov2);
        }
        else if (option == 3) {
            if (movieNames.find(mov1) == movieNames.end() || movieNames.find(mov2) == movieNames.end()) {
                std::cout << "One or both movie titles were not found. Please re-enter.\n";
                continue;
            }

            std::cout << "Select algorithm:\n";
            std::cout << "1. Approach 1 (Genre Overlap)\n";
            std::cout << "2. Approach 2 (Heap: Genre Overlap + Rating)\n";
            std::cout << "Your choice: ";
            std::cin >> algoChoice;
            std::cin.ignore();

            if (algoChoice == 1) {
                PreparedInput input;
                input = input.prepare(mov1, mov2, movieNames);
                storageResult = approach1(input, movieMap);
                dataComputed = true;
                std::cout << "Data computed using Approach 1.\n";
            }
            else if (algoChoice == 2) {
                PreparedInput input;
                input = input.prepare(mov1, mov2, movieNames);
                storageResult = queueApproach(input, movieMap);
                dataComputed = true;
                std::cout << "Data computed using Approach 2.\n";
            }
            else {
                std::cout << "Invalid algorithm choice.\n";
            }
        }
        else if (option == 4) {
            if (!dataComputed) {
                std::cout << "Please compute data first.\n";
                continue;
            }

            if (algoChoice == 1){
                for (int i = 1; i <= 5; ++i){
                    const Storage& bucket = storageResult[i];
                     printResults(storageResult);
                }
            }
            else if (algoChoice == 2) {
                std::cout << "\nTop Recommended Movies (Heap-Based):\n";
                for (Movie* m : topMatches) {
                    std::cout << "- " << m->getName() << " | Rating: " << m->getRating() << "\n";
                }
            }
        }
        else if (option == 5) {
            std::cout << "Exiting Movie Matcher. Goodbye!\n";
            break;
        }
        else {
            std::cout << "Invalid option. Please select 1–5.\n";
        }
    }

    return 0;
}
