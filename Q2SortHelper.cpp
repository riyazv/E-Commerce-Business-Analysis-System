#include "Q2SortHelper.hpp"
#include "Q1ArraySort.hpp"   // for sortTransactionsByDate()
#include <algorithm>
#include <cctype>
#include <iomanip>
#include <iostream>
#include "stringUtils.hpp"

//function for Q2 -> Array Sort Algorithm
void sortAndDisplayQ2Array(Transaction* all, int total) {
    
    //Count matches
    int m = 0;
    for (int i = 0; i < total; ++i) {
        if (toLower(trim(all[i].getCategory())) == "electronics"
         && toLower(trim(all[i].getPaymentMethod())) == "credit card")
        {
            ++m;
        }
    }
    if (m == 0) {
        std::cout << "No Electronics (Credit Card) transactions found.\n";
        return;
    }

    //Collect matches
    Transaction* tmp = new Transaction[m];
    for (int i = 0, idx = 0; i < total; ++i) {
        if (toLower(trim(all[i].getCategory())) == "electronics"
         && toLower(trim(all[i].getPaymentMethod())) == "credit card")
        {
            tmp[idx++] = all[i];
        }
    }

    //Sort by date
    sortTransactionsByDate(tmp, m);

    std::cout << "\n--- Q2: Electronics (Credit Card) Sorted by Date (Array) ---\n"
              << std::left
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
