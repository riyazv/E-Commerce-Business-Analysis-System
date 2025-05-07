#include "DataPreprocessing.hpp"
#include <iostream>
#include <algorithm>
#include "stringUtils.hpp"

// Step 2: Constructor initializes arrays and counters
DataPreprocessing::DataPreprocessing()
{
    cleanedTransactions = new Transaction[MAX_ROWS]; // Allocate memory for cleaned transactions
    cleanedTransactionCount = 0;

    cleanedReviews = new Review[MAX_ROWS]; // Allocate memory for cleaned reviews
    cleanedReviewCount = 0;
}

// Step 3: Destructor releases dynamically allocated memory
DataPreprocessing::~DataPreprocessing()
{
    delete[] cleanedTransactions;
    delete[] cleanedReviews;
}

// Step 4: Clean transaction data (remove empty or invalid rows)
void DataPreprocessing::cleanTransactions(Transaction* transactions, int count)
{
    for (int i = 0; i < count; ++i)
    {
        // Step 4a: Trim and fetch each field from the transaction
        std::string custID = trim(transactions[i].getCustomerID());
        std::string prod = trim(transactions[i].getProduct());
        std::string price = trim(transactions[i].getPrice());
        std::string date = trim(transactions[i].getDate());
        std::string cat = trim(transactions[i].getCategory());
        std::string pay = trim(transactions[i].getPaymentMethod());

        // Step 4b: Skip row if any field is empty or has known invalid content
        if (custID.empty() || prod.empty() || price.empty() || date.empty() || cat.empty() || pay.empty()) continue;
        if (price == "NaN" || date == "Invalid Date") continue;

        // Step 4c: Add valid transaction to cleaned list
        cleanedTransactions[cleanedTransactionCount++] = transactions[i];
    }
}

// Step 5: Clean review data (remove empty or invalid rows)
void DataPreprocessing::cleanReviews(Review* reviews, int count)
{
    for (int i = 0; i < count; ++i)
    {
        // Step 5a: Trim and fetch each field from the review
        std::string prodID = trim(reviews[i].getProductID());
        std::string custID = trim(reviews[i].getCustomerID());
        std::string rating = trim(reviews[i].getRating());
        std::string reviewText = trim(reviews[i].getReviewText());

        // Step 5b: Skip row if any field is empty or has known invalid content
        if (prodID.empty() || custID.empty() || rating.empty() || reviewText.empty()) continue;
        if (rating == "Invalid Rating") continue;

        // Step 5c: Add valid review to cleaned list
        cleanedReviews[cleanedReviewCount++] = reviews[i];
    }
}

// Step 6: Return pointer to cleaned transactions array
Transaction* DataPreprocessing::getCleanedTransactions()
{
    return cleanedTransactions;
}

// Step 7: Return count of valid cleaned transactions
int DataPreprocessing::getCleanedTransactionCount()
{
    return cleanedTransactionCount;
}

// Step 8: Return pointer to cleaned reviews array
Review* DataPreprocessing::getCleanedReviews()
{
    return cleanedReviews;
}

// Step 9: Return count of valid cleaned reviews
int DataPreprocessing::getCleanedReviewCount()
{
    return cleanedReviewCount;
}