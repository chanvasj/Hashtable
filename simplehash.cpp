#include <iostream>
#include <string>
#include <stdexcept> 

#define CAPACITY 50000

// Create Hashtable
class HashTable {
private:
    std::pair<std::string, int> table[CAPACITY];
    

public:
    HashTable();
    void insert(const std::string &key, int value);
    bool contains(const std::string &key) const;
    unsigned long hash_function(const std::string &key) const;
    int get(const std::string &key) const;
};

unsigned long HashTable::hash_function(const std::string &key) const {
    unsigned long hash = 0;
    for (char c : key) {
        if (c >= 'a' && c <= 'z') {
            hash += c - 'a' + 1;
        }
    }
    return hash % CAPACITY;
}

HashTable::HashTable() {
  
    for (int i = 0; i < CAPACITY; ++i) {
        table[i] = std::make_pair("", -1);
    }
}

void HashTable::insert(const std::string &key, int value) {
    unsigned long index = hash_function(key);
    table[index] = std::make_pair(key, value); // Overwrite the value
}

bool HashTable::contains(const std::string &key) const {
    unsigned long index = hash_function(key);
    return table[index].first == key;
}

int HashTable::get(const std::string &key) const {
    unsigned long index = hash_function(key);
    if (table[index].first == key) {
        return table[index].second;
    } else {
        throw std::runtime_error("Key not found");
    }
}

void test_hash_function() {
    HashTable ht;

    std::string str1 = "juan";      // 10 + 21 + 1 + 14 = 46
    std::string str2 = "gisselle";  // 7 + 9 + 19 + 19 + 5 + 12 + 12 + 5 = 88 
    std::string str3 = "alex";      // 1 + 12 + 5 + 24 = 42

    std::cout << "Hash of 'juan': " << ht.hash_function("juan") << std::endl;
    std::cout << "Hash of 'gisselle': " << ht.hash_function("gisselle") << std::endl;
    std::cout << "Hash of 'alex': " << ht.hash_function("alex") << std::endl;
}

void test_insert_function() {
    HashTable ht;

    
    std::pair<std::string, int> key_values_pair[] = {
        {"juan", 46},
        {"gisselle", 88},
        {"alex", 42},
    };

    
    for (const auto &pair : key_values_pair) {
        ht.insert(pair.first, pair.second);
    }

    
    for (const auto &pair : key_values_pair) {
        if (ht.contains(pair.first)) {
            std::cout << "Key '" << pair.first << "' with value " << pair.second << " was inserted correctly." << std::endl;
        } else {
            std::cerr << "Error: Key '" << pair.first << "' was not found in the hashtable." << std::endl;
        }
    }
}

void test_contains_function() {
    HashTable ht;

    ht.insert("juan", 46);
    ht.insert("gisselle", 88);
    ht.insert("alex", 42);

    // Test cases
    std::string test_keys[] = {"juan", "gisselle", "alex", "nonexistent"};

    for (const auto &key : test_keys) {
        if (ht.contains(key)) {
            std::cout << "Key '" << key << "' is present in the hashtable." << std::endl;
        } else {
            std::cerr << "Error: Key '" << key << "' is not present in the hashtable." << std::endl;
        }
    }
}

void test_overwrite_collision() {
    HashTable ht;

   
    ht.insert("juan", 1);

  
    ht.insert("juan", 2);

  
    if (ht.contains("juan")) {
        int value = ht.get("juan");
        if (value == 2) {
            std::cout << "Key 'juan' was correctly overwritten with value 2." << std::endl;
        } else {
            std::cerr << "Error: Key 'juan' has incorrect value " << value << std::endl;
        }
    } else {
        std::cerr << "Error: Key 'juan' was not found in the hashtable." << std::endl;
    }
}

int main() {
    std::cout << "Testing if hash function values are correct" << std::endl;
    test_hash_function();

    std::cout << "Testing key-value pairs" << std::endl;
    test_insert_function();

    std::cout << "Testing contains function" << std::endl;
    test_contains_function();

    std::cout << "Testing overwrite collision handling" << std::endl;
    test_overwrite_collision();

    return 0;
}