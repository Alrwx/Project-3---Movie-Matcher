#pragma once
#include <vector>
#include <string>
#include "Storage.h"

class CustomHashMap {
    //storing the data as structs so its easier to account for linear probing
    struct Data {
        std::string key;
        Storage* value;
        bool taken;
        
        Data() : key(""), value(nullptr), taken(false) {}
    };
    private:
        std::vector<Data> map;
        int numElements;
        float maxLoad;

        unsigned int hash(const std::string& key) const;
        void rehash();
        void checkLoad();

    public:
        CustomHashMap(int startSize = 40, float maximumLoad = 0.75f);
        void insert(const std::string& key, Storage* store);
        bool has(const std::string& key) const;
        Storage* get(const std::string& key) const;
};