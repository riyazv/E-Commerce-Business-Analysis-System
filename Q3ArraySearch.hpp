#ifndef Q3ARRAYSEARCH_HPP
#define Q3ARRAYSEARCH_HPP

#include "CSVReader.hpp" // Step 1: Include Review definition
#include "constants.hpp" // Step 2: Reuse globally defined HASH_TABLE_SIZE_Q3

// Step 3: Function to process 1-star reviews and display the most frequent words
// This function uses an array-based hash table to track word frequency
void analyzeArrayReviews(Review* reviews, int totalReviews);

#endif
