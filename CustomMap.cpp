#include <vector>
#include <string>
#include "Storage.h"
#include "CustomMap.h"


CustomHashMap::CustomHashMap (int startSize, float maxLoad) : map(startSize), numElements(0), maxLoad(maxLoad) {}

unsigned int CustomHashMap::hash(const std::string& key) const {
    //allows for larger values since its not negative
    unsigned int hashValue = 0;
    for (char let : key) {
        hashValue = hashValue * 31 + let;
    }
    return hashValue % map.size();
}

void CustomHashMap::insert(const std::string& key, Storage* value) {
    checkLoad();
    unsigned int id = hash(key);

    while(map[id].taken && map[id].key != key) {
        id = (id + 1) % map.size();
    }

    if (!map[id].taken) {
        map[id].key = key;
        map[id].value = value;
        map[id].taken = true;
        numElements++;
    } else {
        map[id].value = value;
    }
}

bool CustomHashMap::has(const std::string& key) const {
    unsigned int id = hash(key);
    unsigned int start = id; //used to check if the map loops, meaning its not there
    while (map[id].taken) {
        if (map[id].key == key) {
            return true;
        } else {
            id = (id + 1) % map.size();
        }
        if (id == start) {
            break;
        }
    }
    return false;
}

Storage* CustomHashMap::get(const std::string& key) const {
    unsigned int id = hash(key);
    unsigned int start = id;
    while (map[id].taken) {
        if (map[id].key == key) return map[id].value;
        id = (id + 1) % map.size();
        if (id == start) break;
    }
    return nullptr;
}

void CustomHashMap::checkLoad() {
    float load;
    load = (float)numElements / map.size();
    if (load > maxLoad) {
        rehash();
    }
}

void CustomHashMap::rehash() {
    int newSize = map.size() * 2;
    std::vector<Data> newMap(newSize);

    //repopulate the map
    for (unsigned int i = 0; i < map.size(); ++i) {
        const Data& entry = map[i];
        if (entry.taken) {
            // Compute hash for new map size
            unsigned int hashValue = 0;
            for (char let : entry.key) {
                hashValue = hashValue * 31 + let; //allows overflow
            }
            unsigned int id = hashValue % newSize;

            // Linear probe to find empty spot
            while (newMap[id].taken) {
                id = (id + 1) % newSize;
            }
            newMap[id] = entry;
        }
    }
    map = newMap;
}