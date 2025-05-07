#include "CSVReader.hpp"
#include "stringUtils.hpp"
#include "Q2ArraySearch.hpp"
#include "Q1ArraySort.hpp"
#include <iostream>
#include <iomanip>
#include <string>

//Q2 -> Array Sequential Search Algorithm
//% of electronic/card payment
double calculateElectronicsCreditCardPercentage(Transaction* transactions, int size) {
    int totalElectronics = 0;
    int creditCardPurchases = 0;
    for (int i = 0; i < size; ++i) {
        // always use trimmed + lowercase values
        auto cat = toLower(trim(transactions[i].getCategory()));
        auto pay = toLower(trim(transactions[i].getPaymentMethod()));
    
        if (cat == "electronics") {
            ++totalElectronics;
            if (pay == "credit card") {
                ++creditCardPurchases;
            }
        }
    }
    
    return totalElectronics
         ? (static_cast<double>(creditCardPurchases) / totalElectronics) * 100.0
         : 0.0;
}

//Q2 -> Array Sequential Search Algorithm
//Displays all matching Electronics+Credit Card transactions
void displayMatchingTransactions(Transaction* transactions, int size) {
    std::cout << std::fixed << std::setprecision(2)
              << "\nMatching Transactions (Electronics + Credit Card):\n"
              << "--------------------------------------------------------------------------------\n"
              << std::left
                 << std::setw(15) << "Customer ID"
                 << std::setw(20) << "Product"
                 << std::setw(15) << "Category"
                 << std::setw(10) << "Price"
                 << std::setw(15) << "Date"
                 << std::setw(20) << "Payment Method" << "\n"
              << "--------------------------------------------------------------------------------\n";
    for (int i = 0; i < size; ++i) {
        auto cat = toLower(trim(transactions[i].getCategory()));
        auto pay = toLower(trim(transactions[i].getPaymentMethod()));
        if ( cat =="electronics" && pay == "credit card"){
            auto &t = transactions[i];
            std::cout << std::left
                      << std::setw(15) << t.getCustomerID()
                      << std::setw(20) << t.getProduct()
                      << std::setw(15) << t.getCategory()
                      << std::setw(10) << t.getPrice()
                      << std::setw(15) << t.getDate()
                      << std::setw(20) << t.getPaymentMethod() << "\n";
        }
    }
    std::cout << "--------------------------------------------------------------------------------\n";
}

//Q1 -> Array Sort Algorithm
//QuickSort to sort transactions by date
void Q1ArrayDateSort::quickSortByDate(Transaction* transactions, int low, int high) {
    if (low < high) {
        int pi = partition(transactions, low, high);
        quickSortByDate(transactions, low, pi - 1);
        quickSortByDate(transactions, pi + 1, high);
    }
}

int Q1ArrayDateSort::partition(Transaction* transactions, int low, int high) {
    std::string pivot = transactions[high].getDate();  // Get date from Transaction
    int i = (low - 1);
    for (int j = low; j < high; j++) {
        if (transactions[j].getDate() <= pivot) {  // Compare dates
            i++;
            std::swap(transactions[i], transactions[j]);
        }
    }
    std::swap(transactions[i + 1], transactions[high]);
    return (i + 1);
}
