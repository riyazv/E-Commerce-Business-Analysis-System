#ifndef Q2ARRAYSEARCH_HPP
#define Q2ARRAYSEARCH_HPP

#include "CSVReader.hpp"  // Step 1: Include Transaction definition and data access

// Step 2: Calculate the percentage of Electronics purchases made using Credit Card
// Uses category and payment method fields
double calculateElectronicsCreditCardPercentage(Transaction* transactions, int size);

// Step 3: Display the list of Electronics purchases made using Credit Card
// Output formatted in table view
void displayMatchingTransactions(Transaction* transactions, int size);

#endif
