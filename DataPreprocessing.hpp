#ifndef DATAPREPROCESSING_HPP
#define DATAPREPROCESSING_HPP

#include "CSVReader.hpp"
#include <string>

// Step 1: Declare the DataPreprocessing class
class DataPreprocessing 
{
private:
    Transaction* cleanedTransactions;  // Step 2: Pointer to cleaned transaction data
    int cleanedTransactionCount;       // Step 3: Number of valid cleaned transactions

    Review* cleanedReviews;            // Step 4: Pointer to cleaned review data
    int cleanedReviewCount;            // Step 5: Number of valid cleaned reviews

public:
    // Step 6: Constructor to allocate memory
    DataPreprocessing();

    // Step 7: Destructor to free allocated memory
    ~DataPreprocessing();

    // Step 8: Clean invalid or empty transaction rows
    void cleanTransactions(Transaction* transactions, int count);

    // Step 9: Clean invalid or empty review rows
    void cleanReviews(Review* reviews, int count);

    // Step 10: Get pointer to cleaned transaction list
    Transaction* getCleanedTransactions();

    // Step 11: Get total number of cleaned transactions
    int getCleanedTransactionCount();

    // Step 12: Get pointer to cleaned review list
    Review* getCleanedReviews();

    // Step 13: Get total number of cleaned reviews
    int getCleanedReviewCount();
};

#endif
