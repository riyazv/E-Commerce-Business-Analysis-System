#ifndef Q2_LINKED_LIST_FILTER_HPP
#define Q2_LINKED_LIST_FILTER_HPP

#include <string>
#include <algorithm>
#include <cctype>
#include <iomanip>
#include "CSVReader.hpp"     
#include "DataPreprocessing.hpp"     
#include "Q1LinkedListSort.hpp"   //sorts a Transaction* C-array
#include "stringUtils.hpp"

//Q2 Linked list sort
inline void sortAndDisplayQ2List(Transaction* all, int total) {
    // 1) Count matches
    int m = 0;
    for (int i = 0; i < total; ++i) {
        auto cat = toLower(trim(all[i].getCategory()));
        auto pay = toLower(trim(all[i].getPaymentMethod()));
        if (cat == "electronics" && pay == "credit card"){
            ++m;
        }
    }

    //copying into a temp c-array
    Transaction* tmp = new Transaction[m];
    for (int i = 0, idx = 0; i < total; ++i) {
        auto cat = toLower(trim(all[i].getCategory()));
        auto pay = toLower(trim(all[i].getPaymentMethod()));
        if (cat == "electronics" && pay == "credit card") {
            tmp[idx++] = all[i];
        }
    }

    if (m == 0) {
        std::cout << "No Electronics (Credit Card) transactions found.\n";
        return;
    }

    //Sort with linked-list merge-sort
    sortTransactionsLinkedList(tmp, m);

    //Print table
    std::cout << std::left
              << std::setw(12) << "Date"
              << std::setw(15) << "CustomerID"
              << std::setw(20) << "Product"
              << std::setw(10) << "Price"
              << std::setw(15) << "Category"
              << std::setw(20) << "Payment"
              << "\n" << std::string(92, '-') << "\n";
    for (int i = 0; i < m; ++i) {
        auto &t = tmp[i];
        std::cout << std::left
                  << std::setw(12) << t.getDate()
                  << std::setw(15) << t.getCustomerID()
                  << std::setw(20) << t.getProduct()
                  << std::setw(10) << t.getPrice()
                  << std::setw(15) << t.getCategory()
                  << std::setw(20) << t.getPaymentMethod()
                  << "\n";
    }
    std::cout << std::string(92, '-') << "\n";

    delete[] tmp;
}

#endif 
