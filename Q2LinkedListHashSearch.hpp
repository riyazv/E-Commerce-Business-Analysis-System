#ifndef Q2LINKEDLISTHASHSEARCH_HPP
#define Q2LINKEDLISTHASHSEARCH_HPP

#include "CSVReader.hpp"
#include "stringUtils.hpp"
#include <string>

// Step 1: Set the hash table size — using a prime number helps reduce collisions
const int HASH_TABLE_SIZE_Q2 = 211;

// Step 2: Define a node structure to store a transaction and a pointer to the next node
struct HashNodeQ2 
{
    Transaction data; // Holds a transaction object
    HashNodeQ2* next; // Pointer to next node in the chain

    HashNodeQ2(Transaction t); // Constructor
};

// Step 3: Define a class for Linked List Hash Table Search functionality for Q2
class LinkedListHashSearchQ2 
{
private:
    HashNodeQ2* table[HASH_TABLE_SIZE_Q2]; // Array of linked lists (chaining)

    // Step 4: Utility function to hash a string key
    int hash(const std::string& key);

    // Step 5: Converts input string to lowercase for case-insensitive matching
    std::string toLower(const std::string& s);

    // Step 6: Combines category and payment method into a single searchable key
    std::string toKey(const std::string& category, const std::string& payment);

public:
    // Step 7: Constructor initializes empty table
    LinkedListHashSearchQ2();

    // Step 8: Destructor frees memory using clear()
    ~LinkedListHashSearchQ2();

    // Step 9: Insert transaction into hash table based on category+payment key
    void insert(Transaction t);

    // Step 10: Search for Electronics + Credit Card transactions and print results
    void searchElectronicsCreditCard();

    // Step 11: Clear all nodes in the hash table to free memory
    void clear();
};

#endif