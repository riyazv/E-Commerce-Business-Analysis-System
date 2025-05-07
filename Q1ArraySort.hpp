#ifndef Q1ARRAYSORT_HPP
#define Q1ARRAYSORT_HPP

#include "CSVReader.hpp"  // Include CSVReader for the Transaction class

class Q1ArrayDateSort {
public:
    void quickSortByDate(Transaction* transactions, int low, int high);  // Use Transaction class
private:
    int partition(Transaction* transactions, int low, int high);  // Use Transaction class
};

void sortTransactionsByDate(Transaction* transactions, int count);

#endif
