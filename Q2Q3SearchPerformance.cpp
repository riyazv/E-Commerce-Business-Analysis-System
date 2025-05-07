#include "Q2Q3SearchPerformance.hpp"
#include "stringUtils.hpp"
#include "Q1LinkedListSort.hpp" //sortTransactionsLinkedList()
#include "Q2ArraySearch.hpp"
#include "Q2LinkedListHashSearch.hpp"
#include "Q3LinkedListHashSearch.hpp"
#include "Q3ArraySearch.hpp"
#include "Q3_LinkedListFilter.hpp" //splitList/mergeSort(), sortAndDisplayWordCounts()
#include "Q1ArraySort.hpp"
#include "Q3ReviewWordSort.hpp" //WordCount, Q3ArraySort
#include <iostream>
#include <iomanip>
#include <chrono>

//--Q2 Perf Opt
//Array Sort Alg
void runQ2ArraySortTest(Transaction* transactions, int total) {
    const int TEST_RUNS = 5;
    std::cout << "\n--- Q2 Array Sort Performance Test ---\n";

    // estimate memory
    size_t memoryUsed = sizeof(Transaction) * total;

    long long totalNs = 0;
    for (int run = 1; run <= TEST_RUNS; ++run) {
        // 1) filter Electronics + Credit Card
        int m = 0;
        for (int i = 0; i < total; ++i) {
            auto cat = toLower(trim(transactions[i].getCategory()));
            auto pay = toLower(trim(transactions[i].getPaymentMethod()));
            if (cat == "electronics" && pay == "credit card") ++m;
        }
        Transaction* tmp = new Transaction[m];
        for (int i = 0, j = 0; i < total; ++i) {
            auto cat = toLower(trim(transactions[i].getCategory()));
            auto pay = toLower(trim(transactions[i].getPaymentMethod()));
            if (cat == "electronics" && pay == "credit card")
                tmp[j++] = transactions[i];
        }

        // 2) time the array‐sort
        auto t0 = std::chrono::high_resolution_clock::now();
        sortTransactionsByDate(tmp, m);
        auto t1 = std::chrono::high_resolution_clock::now();

        long long ns = std::chrono::duration_cast<std::chrono::nanoseconds>(t1 - t0).count();
        totalNs += ns;

        std::cout << "Test " << std::setw(2) << run << ": " << ns << " ns\n";

        delete[] tmp;
    }

    long long totalMs = totalNs / 1'000'000;
    std::cout << "\nTotal for " << TEST_RUNS << " runs: "
              << totalNs << " ns (" << totalMs << " ms)\n"
              << "Estimated Memory Used: " << memoryUsed << " bytes\n\n";
}


//Q2 -> Linked List Sort Alg
void runQ2LinkedListSortTest(Transaction* transactions, int total) {
    const int TEST_RUNS = 10;
    std::cout << "\n    Q2 Linked List Sort Performance Test    ";
    std::cout << "\n--------------------------------------------" << std::endl;

    //Estimate memory usage
    size_t memoryUsed = sizeof(Transaction) * total;

    long long totalNs = 0;  //totals all runs

    for (int run = 1; run <= TEST_RUNS; ++run) {
        //filter electronics + credit card
        int m = 0;
        for (int i = 0; i < total; ++i) {
            auto cat = toLower(trim(transactions[i].getCategory()));
            auto pay = toLower(trim(transactions[i].getPaymentMethod()));
            if (cat == "electronics" && pay == "credit card") ++m;
        }
        Transaction* tmp = new Transaction[m];
        for (int i = 0, j = 0; i < total; ++i) {
            auto cat = toLower(trim(transactions[i].getCategory()));
            auto pay = toLower(trim(transactions[i].getPaymentMethod()));
            if (cat == "electronics" && pay == "credit card") {
                tmp[j++] = transactions[i];
            }
        }

        //calculating ns
        auto start = std::chrono::high_resolution_clock::now();
        sortTransactionsLinkedList(tmp, m);
        auto end   = std::chrono::high_resolution_clock::now();

        long long ns = std::chrono::duration_cast<std::chrono::nanoseconds>(end - start).count();
        totalNs += ns;

        std::cout << "Test " << std::setw(2) << run << "\t  : " 
                  << ns << " ns\n";

        delete[] tmp;
    }

    // 3) Report totals
    long long totalMs = totalNs / 1'000'000;  // convert ns → ms
        // build the two summary lines
        std::string line1 = 
        "Total Time for " + std::to_string(TEST_RUNS) 
        + " runs: " + std::to_string(totalNs) 
        + " ns (" + std::to_string(totalMs) + " ms)";
        std::string line2 = 
        "Estimated Memory Used: " + std::to_string(memoryUsed) + " bytes";

        // compute the box width
        size_t w = std::max(line1.size(), line2.size());

        // top/bottom border
        std::string border(w + 4, '-');

        // print the box
        std::cout 
            << "\n" << border << "\n"
            << "| " << std::left << std::setw(w) << line1 << " |\n"
            << "| " << std::left << std::setw(w) << line2 << " |\n"
            << border << "\n\n";
}

//--Q3 Word Freq
//Array Sort Alg
void runQ3ArraySortTest( Review* reviews, int total ) {
    const int TEST_RUNS = 5;
    std::cout << "\n--- Q3 Array Sort Performance ---\n";
    size_t memoryUsed = sizeof(Review) * total;
    auto overallStart = std::chrono::high_resolution_clock::now();

    for (int test = 1; test <= TEST_RUNS; ++test) {
        std::cout << "\nTest " << test << ":\n";
        analyzeArrayReviews(reviews, total);
    }

    auto overallEnd = std::chrono::high_resolution_clock::now();

    std::cout
      << "\nTotal Execution Time (" << TEST_RUNS << " runs): "
      << std::chrono::duration_cast<std::chrono::milliseconds>(overallEnd - overallStart).count()
      << " ms\nEstimated Memory Used: " << memoryUsed << " bytes\n";
}


//Q3 Word Freq Perf -> Linked List Sort Alg
void runQ3LinkedListSortTest(Review* reviews, int total) {
    const int TEST_RUNS = 5;
    std::cout << "\n--- Q3 Linked List Sort Performance Test ---\n";

    size_t memoryUsed = sizeof(Review) * total;
    long long totalNs = 0;

    for (int run = 1; run <= TEST_RUNS; ++run) {
        std::cout << "\nTest " << run << ":\n";

        // 1) Build & populate hash table
        LinkedListHashSearchQ3 hashSearch;
        hashSearch.processOneStarReviews(reviews, total);

        // 2) Pull into single list
        WordNode* head = hashSearch.releaseWordList();

        // 3) Time the sort
        auto t0 = std::chrono::high_resolution_clock::now();
        mergeSort(&head);
        auto t1 = std::chrono::high_resolution_clock::now();

        long long elapsedNs = std::chrono::duration_cast<std::chrono::nanoseconds>(t1 - t0).count();
        totalNs += elapsedNs;

        // 4) Print timing
        std::cout << "  Duration: " << elapsedNs << " ns\n";

        // 5) Pretty-print top 10 in a table
        const int COL1 = 20, COL2 = 8;
        std::cout
          << "+" << std::string(COL1 + COL2 + 3, '-') << "+\n"
          << "| " << std::left << std::setw(COL1) << "Word"
                 << " | " << std::right << std::setw(COL2) << "Count"
                 << " |\n"
          << "+" << std::string(COL1 + COL2 + 3, '-') << "+\n";

        WordNode* cur = head;
        for (int i = 0; cur && i < 10; ++i, cur = cur->next) {
            std::cout
              << "| " << std::left << std::setw(COL1) << cur->word
                     << " | " << std::right << std::setw(COL2) << cur->count
                     << " |\n";
        }
        std::cout << "+" << std::string(COL1 + COL2 + 3, '-') << "+\n";

        // 6) Free the list
        while (head) {
            WordNode* tmp = head;
            head = head->next;
            delete tmp;
        }
    }

    // 7) Summary
    std::cout << "\nTotal for " << TEST_RUNS << " runs: " 
              << totalNs << " ns (" << (totalNs / 1'000'000) << " ms)\n"
              << "Estimated Memory Used: " << memoryUsed << " bytes\n\n";
}

// Step 1: Run and time Array Sequential Search for Q2
void runQ2ArraySequentialTest(Transaction* transactions, int total)
{
    const int TEST_RUNS = 5;

    std::cout << "\n--- Q2 Array Sequential Search Performance ---\n";

    // Step 2: Calculate memory usage for the array
    size_t memoryUsed = sizeof(Transaction) * total;

    // Step 3: Start timing for all runs
    auto overallStart = std::chrono::high_resolution_clock::now();

    for (int test = 1; test <= TEST_RUNS; ++test)
    {
        std::cout << "\nTest " << test << ":\n";

        // Step 4: Calculate and print Electronics + Credit Card percentage
        double percentage = calculateElectronicsCreditCardPercentage(transactions, total);
        std::cout << "\nPercentage of Electronics purchases made with Credit Card: "
            << std::fixed << std::setprecision(2) << percentage << "%\n";

        // Step 5: Display matching transactions
        displayMatchingTransactions(transactions, total);
    }

    // Step 6: End timing and calculate duration
    auto overallEnd = std::chrono::high_resolution_clock::now();
    long long totalTime = std::chrono::duration_cast<std::chrono::milliseconds>(overallEnd - overallStart).count();

    // Step 7: Display results
    std::cout << "\nTotal Execution Time (" << TEST_RUNS << " runs): " << totalTime << " ms" << std::endl;
    std::cout << "Estimated Memory Used: " << memoryUsed << " bytes" << std::endl;
}

// Step 8: Run and time Linked List Hash Table Search for Q2
void runQ2LinkedListTest(Transaction* transactions, int total)
{
    const int TEST_RUNS = 5;

    std::cout << "\n--- Q2 LinkedList Hash Table Search Performance ---\n";

    size_t memoryUsed = sizeof(Transaction) * total;

    auto overallStart = std::chrono::high_resolution_clock::now();

    for (int test = 1; test <= TEST_RUNS; ++test)
    {
        std::cout << "\nTest " << test << ":\n";

        // Step 9: Insert all transactions into the hash table
        LinkedListHashSearchQ2 hashSearch;
        for (int i = 0; i < total; ++i)
        {
            hashSearch.insert(transactions[i]);
        }

        // Step 10: Search and display results
        hashSearch.searchElectronicsCreditCard();
    }

    auto overallEnd = std::chrono::high_resolution_clock::now();
    long long totalTime = std::chrono::duration_cast<std::chrono::milliseconds>(overallEnd - overallStart).count();

        {
        // prepare the two summary lines
        std::string line1 = 
            "Total Execution Time (" + std::to_string(TEST_RUNS) + " runs): " 
            + std::to_string(totalTime) + " ms";
        std::string line2 = 
            "Estimated Memory Used: " + std::to_string(memoryUsed) + " bytes";

        // compute the width of the box
        size_t w = std::max(line1.size(), line2.size());

        // build top/bottom border
        std::string border(w + 4, '-');

        // print the box
        std::cout 
            << "\n" << border << "\n"
            << "| " << std::left << std::setw(w) << line1 << " |\n"
            << "| " << std::left << std::setw(w) << line2 << " |\n"
            << border << "\n";
    }
}

// Step 11: Run and time Array Hash Table analysis for Q3
void runQ3ArrayTest(Review* reviews, int total)
{
    const int TEST_RUNS = 5;

    std::cout << "\n--- Q3 Array Hash Table Word Frequency ---\n";

    size_t memoryUsed = sizeof(Review) * total;

    auto overallStart = std::chrono::high_resolution_clock::now();

    for (int test = 1; test <= TEST_RUNS; ++test)
    {
        std::cout << "\nTest " << test << ":\n";
        analyzeArrayReviews(reviews, total);
    }

    auto overallEnd = std::chrono::high_resolution_clock::now();
    long long totalTime = std::chrono::duration_cast<std::chrono::milliseconds>(overallEnd - overallStart).count();

    std::cout << "\nTotal Execution Time (" << TEST_RUNS << " runs): " << totalTime << " ms" << std::endl;
    std::cout << "Estimated Memory Used: " << memoryUsed << " bytes" << std::endl;
}

// Step 12: Run and time Linked List Hash Table analysis for Q3
void runQ3LinkedListTest(Review* reviews, int total)
{
    const int TEST_RUNS = 5;

    std::cout << "\n--- Q3 LinkedList Hash Table Word Frequency ---\n";

    size_t memoryUsed = sizeof(Review) * total;

    auto overallStart = std::chrono::high_resolution_clock::now();

    for (int test = 1; test <= TEST_RUNS; ++test)
    {
        std::cout << "\nTest " << test << ":\n";

        LinkedListHashSearchQ3 hashSearch;
        hashSearch.processOneStarReviews(reviews, total);
        hashSearch.displayTopWords(3);
    }

    auto overallEnd = std::chrono::high_resolution_clock::now();
    long long totalTime = std::chrono::duration_cast<std::chrono::milliseconds>(overallEnd - overallStart).count();

    std::cout << "\nTotal Execution Time (" << TEST_RUNS << " runs): " << totalTime << " ms" << std::endl;
    std::cout << "Estimated Memory Used: " << memoryUsed << " bytes" << std::endl;
}