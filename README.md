# MovieMatcher

Movie Matcher is a command-line C++ program that recommends movies based on genre similarity and viewer ratings. Users input two movie titles, and the program analyzes their genres to find the best-matching movies from a dataset of over 100,000 entries.

## Features Include
  - Comparing two movies and find others that share similar genres
  - Choose between two recommendation approaches:
      - **Approach 1**: Genre overlap (custom hash-map and genre similarity)
      - **Approach 2**: Genre overlap + Rating (custom priority_queue)
  - Parses and stores datasets from MovieLens [https://grouplens.org/datasets/movielens/]

## File Structure 
Project-3---Movie-Matcher/
├── .vscode/ 
│ ├── c_cpp_properties.json
│ ├── launch.json
│ ├── settings.json
├── files/ 
│ ├── csvratings.csv
│ ├── movies.csv
├── test/
│ ├── movietest.csv
│ ├── ratingtest.csv

├── CMakeLists.txt 
├── MovieMatcher.exe 

Source files
├── main.cpp 
├── CustomMap.cpp / CustomMap.h 
├── Storage.cpp / Storage.h
├── movie.cpp / movie.h
├── parsing.cpp / parsing.h
├── prepareInput.cpp / prepareInput.h

## How to Run
1. Extract folder contents.
2. Open a terminal (e.g. PowerShell)
3. Navigate to project folder (e.g. cd "C:\Users\YourName\Desktop\Project-3---Movie-Matcher-main")
4. Run the MovieMatcher.exe file (e.g. .\MovieMatcher.exe)
