#include "Q3LinkedListHashSearch.hpp"
#include <iostream>
#include <sstream>
#include <cctype>
#include <algorithm>
#include <iomanip>

// Step 1: Constructor for WordNode, initializes the word, count, and pointer
WordNode::WordNode(const std::string& w) 
{
    word = w;
    count = 1;
    next = nullptr;
}

// Step 2: Constructor for LinkedListHashSearchQ3, initializes all table slots to nullptr
LinkedListHashSearchQ3::LinkedListHashSearchQ3() 
{
    for (int i = 0; i < HASH_TABLE_SIZE_Q3; ++i)
        table[i] = nullptr;
}

// Step 3: Destructor calls clear() to free all memory
LinkedListHashSearchQ3::~LinkedListHashSearchQ3() 
{
    clear();
}

// Step 4: Hash function to generate an index from a word (polynomial rolling hash)
int LinkedListHashSearchQ3::hash(const std::string& word) 
{
    int hashVal = 0;
    for (char c : word)
        hashVal = (hashVal * 31 + c) % HASH_TABLE_SIZE_Q3;
    return hashVal;
}

// Step 5: Cleans a word by removing non-alphanumeric characters and converting to lowercase
std::string LinkedListHashSearchQ3::cleanWord(const std::string& word) 
{
    std::string cleaned;
    for (char c : word)
        if (std::isalnum(c))
            cleaned += std::tolower(c);
    return cleaned;
}

// Step 6: Inserts a word into the hash table (or increments its count if it already exists)
void LinkedListHashSearchQ3::insertWord(const std::string& word)
{
    std::string cleaned = cleanWord(word);
    if (cleaned.empty()) return;

    int index = hash(cleaned);
    WordNode* node = table[index];

    // Check if word already exists in chain
    while (node) 
    {
        if (node->word == cleaned) 
        {
            node->count++;
            return;
        }
        node = node->next;
    }

    // Insert new word at head of list
    WordNode* newNode = new WordNode(cleaned);
    newNode->next = table[index];
    table[index] = newNode;
}

// Step 7: Process all 1-star reviews and insert words into the hash table
void LinkedListHashSearchQ3::processOneStarReviews(Review* reviews, int count) 
{
    for (int i = 0; i < count; ++i) 
    {
        if (reviews[i].getRating() == "1") 
        {
            std::stringstream ss(reviews[i].getReviewText());
            std::string word;
            while (ss >> word)
                insertWord(word);
        }
    }
}

// Step 8: Collect all words from the hash table and display the top N frequent ones
void LinkedListHashSearchQ3::displayTopWords(int topN) 
{
    const int MAX_COLLECT = 1000;
    WordNode* allWords[MAX_COLLECT];
    int count = 0;

    // Step 8a: Collect pointers to all WordNodes into an array
    for (int i = 0; i < HASH_TABLE_SIZE_Q3; ++i) 
    {
        WordNode* node = table[i];
        while (node && count < MAX_COLLECT) 
        {
            allWords[count++] = node;
            node = node->next;
        }
    }

    // Step 8b: Sort words in descending order of frequency (selection sort)
    for (int i = 0; i < count - 1; ++i) 
    {
        for (int j = i + 1; j < count; ++j) 
        {
            if (allWords[j]->count > allWords[i]->count) 
            {
                WordNode* temp = allWords[i];
                allWords[i] = allWords[j];
                allWords[j] = temp;
            }
        }
    }

    // Step 8c: Display the top N frequent words
    std::cout << "\nTop " << topN << " Frequent Words in 1-Star Reviews:\n";
    std::cout << "---------------------------------------------\n";
    for (int i = 0; i < topN && i < count; ++i) {
        std::cout << std::setw(15) << allWords[i]->word << " : " << allWords[i]->count << std::endl;
    }
}

//function for Q3 -> Linked List Sort
WordNode* LinkedListHashSearchQ3::releaseWordList() {
    WordNode* head = nullptr;
    WordNode** tail = &head;
    for (int i = 0; i < HASH_TABLE_SIZE_Q3; ++i) {
        WordNode* node = table[i];
        while (node) {
            WordNode* next = node->next;
            node->next = nullptr;
            *tail = node;
            tail = &node->next;
            node = next;
        }
        table[i] = nullptr;
    }
    return head;
}

// Step 9: Clear all nodes in the hash table to release memory
void LinkedListHashSearchQ3::clear() 
{
    for (int i = 0; i < HASH_TABLE_SIZE_Q3; ++i) 
    {
        WordNode* node = table[i];
        while (node) 
        {
            WordNode* temp = node;
            node = node->next;
            delete temp;
        }
        table[i] = nullptr;
    }
}
