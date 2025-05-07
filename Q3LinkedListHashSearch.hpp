#ifndef Q3LINKEDLISTHASHSEARCH_HPP
#define Q3LINKEDLISTHASHSEARCH_HPP

#include "CSVReader.hpp"
#include "constants.hpp"  // Step 1: Reuse HASH_TABLE_SIZE_Q3 for consistent hash table sizing

// Step 2: Node structure to store a word, its frequency count, and a link to the next node
struct WordNode 
{
    std::string word;  // The word itself
    int count; // Frequency of the word
    WordNode* next;  // Pointer to the next word node in the linked list

    WordNode(const std::string& w);  // Step 2a: Constructor to initialize values
};

// Step 3: Class to manage word frequency using Linked List Hash Table
class LinkedListHashSearchQ3 
{
private:
    WordNode* table[HASH_TABLE_SIZE_Q3];  // Step 4: Hash table using chaining with linked lists

    // Step 5: Hash function to convert word to index
    int hash(const std::string& word);

    // Step 6: Utility to clean a word (remove punctuation, lowercase)
    std::string cleanWord(const std::string& word);

public:
    // Step 7: Constructor initializes empty hash table
    LinkedListHashSearchQ3();

    // Step 8: Destructor to clear all dynamically allocated memory
    ~LinkedListHashSearchQ3();

    // Step 9: Insert a cleaned word into the hash table
    void insertWord(const std::string& word);

    // Step 10: Process only 1-star reviews and collect words
    void processOneStarReviews(Review* reviews, int count);

    // Step 11: Display the most frequent words found
    void displayTopWords(int topN);

    //singly-linked list, function for q3 -> linked list sort
    WordNode* releaseWordList();

    // Step 12: Clear the entire hash table (called by destructor)
    void clear();
};

#endif
