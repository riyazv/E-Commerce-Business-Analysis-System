#include "Q3ArraySearch.hpp"
#include <iostream>
#include <string>
#include <algorithm>
#include <cctype>

// Step 1: Define a hash table entry structure to store words and their frequencies
struct WordEntry 
{
    std::string word;
    int count;
    bool isOccupied;

    // Step 2: Default constructor initializes fields
    WordEntry() : word(""), count(0), isOccupied(false) {}
};

// Step 3: Hash function using polynomial rolling hash method for a given word
int hashFunctionQ3(const std::string& key) 
{
    const int prime = 31;
    int hash = 0;
    for (char c : key) 
    {
        hash = (hash * prime + c) % HASH_TABLE_SIZE_Q3;
    }
    return hash;
}

// Step 4: Insert word into hash table or update existing word frequency
void insertOrUpdateQ3(WordEntry* table, const std::string& word) 
{
    int index = hashFunctionQ3(word);
    int start = index;

    // Step 4a: Use linear probing to find an empty slot or existing word
    while (true) 
    {
        if (!table[index].isOccupied) 
        {
            table[index].word = word;
            table[index].count = 1;
            table[index].isOccupied = true;
            return;
        }
        else if (table[index].word == word) 
        {
            table[index].count++;
            return;
        }

        index = (index + 1) % HASH_TABLE_SIZE_Q3;
        if (index == start) return; // Table is full
    }
}

// Step 5: Preprocess a word by removing non-alphanumeric characters and converting to lowercase
std::string processWordQ3(const std::string& word) 
{
    std::string processed;
    for (char c : word) 
    {
        if (std::isalnum(c)) processed += std::tolower(c);
    }
    return processed;
}

// Step 6: Extract valid entries from hash table into a result array
void extractQ3Entries(const WordEntry* table, WordEntry* result, int& size) 
{
    size = 0;
    for (int i = 0; i < HASH_TABLE_SIZE_Q3; ++i) 
    {
        if (table[i].isOccupied) 
        {
            result[size++] = table[i];
        }
    }
}

// Step 7: Analyze 1-star reviews and display top 10 frequent words using an array-based hash table
void analyzeArrayReviews(Review* reviews, int totalReviews) 
{
    // Step 7a: Allocate hash table
    WordEntry* hashTable = new WordEntry[HASH_TABLE_SIZE_Q3];

    // Step 7b: Process each review if it has a 1-star rating
    for (int i = 0; i < totalReviews; ++i) 
    {
        if (reviews[i].getRating() != "1") continue;

        std::string text = reviews[i].getReviewText();
        std::string current;

        // Step 7c: Tokenize the text into words
        for (char c : text) 
        {
            if (std::isspace(c)) 
            {
                if (!current.empty()) 
                {
                    std::string processed = processWordQ3(current);
                    if (!processed.empty()) insertOrUpdateQ3(hashTable, processed);
                    current.clear();
                }
            }
            else 
            {
                current += c;
            }
        }

        // Step 7d: Process any remaining word at the end
        if (!current.empty()) 
        {
            std::string processed = processWordQ3(current);
            if (!processed.empty()) insertOrUpdateQ3(hashTable, processed);
        }
    }

    // Step 8: Extract and sort the word entries by frequency
    WordEntry* entries = new WordEntry[HASH_TABLE_SIZE_Q3];
    int size = 0;
    extractQ3Entries(hashTable, entries, size);

    std::sort(entries, entries + size, [](const WordEntry& a, const WordEntry& b) 
        {
        return a.count > b.count;
        });

    // Step 9: Display top 10 frequent words
    std::cout << "\nMost frequent words in 1-star reviews (Array Hash Table):\n";
    for (int i = 0; i < 10 && i < size; ++i) 
    {
        std::cout << entries[i].word << ": " << entries[i].count << std::endl;
    }

    // Step 10: Cleanup
    delete[] entries;
    delete[] hashTable;
}
