// Q1SortPerformance.cpp
#include "Q1_SortPerformance.hpp"
#include "Q1ArraySort.hpp"         //sortTransactionsByDate()
#include "Q1LinkedListSort.hpp"    //sortTransactionsLinkedList()
#include "PerformanceHelper.hpp"   //for timer and memory estimator
#include <iostream>
#include <algorithm>
#include <iomanip>

static const int TEST_RUNS = 5;

void runQ1ArraySortTest(Transaction* all, int total) {
    std::cout << "\n--- Q1 Array Sort Performance ---\n";
    // Estimate memory: size of Transaction * total rows
    size_t mem = sizeof(Transaction) * total;

    Timer timer;
    timer.begin();
    for (int i = 0; i < TEST_RUNS; ++i) {
        // copy data into a temp buffer
        Transaction* tmp = new Transaction[total];
        std::copy(all, all + total, tmp);

        // perform the sort
        sortTransactionsByDate(tmp, total);

        delete[] tmp;
    }
    double ms = timer.endMilliseconds();

    std::cout << "Average time (" << TEST_RUNS << " runs): "
              << std::fixed << std::setprecision(2)
              << (ms / TEST_RUNS) << " ms\n";
    std::cout << "Estimated memory used: " << mem << " bytes\n";
}

void runQ1LinkedListSortTest(Transaction* all, int total) {
    std::cout << "\n--- Q1 Linked List Sort Performance ---\n";
    size_t mem = sizeof(Transaction) * total;

    Timer timer;
    timer.begin();
    for (int i = 0; i < TEST_RUNS; ++i) {
        Transaction* tmp = new Transaction[total];
        std::copy(all, all + total, tmp);

        sortTransactionsLinkedList(tmp, total);

        delete[] tmp;
    }
    double ms = timer.endMilliseconds();

    std::cout
    << "--------------------------------------- \n"
       "| Average time (" << TEST_RUNS << " runs): " << std::fixed << std::setprecision(2)
    << (ms/TEST_RUNS) << " ms       | \n"
       "| Estimated memory used: " << mem << " bytes  |\n"
       " -------------------------------------- \n";

}
